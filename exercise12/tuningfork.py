import pyfftw
import numpy as np
import matplotlib.pyplot as plt

## Read signals from three .dat files
def read_signal(file_path):
    try:
        data = np.loadtxt(file_path)
        return data
    except FileNotFoundError:
        print(f"File not found: {file_path}")
        return None
    
signal1 = read_signal('sample1.dat')
signal2 = read_signal('sample2.dat')
signal3 = read_signal('sample3.dat')

## Plot time-domain signals. File has t and amplitude columns
## Create a subplot for each signal
## Scale y-axis between 2 and 3
def plot_time_domain(signals, labels, strip_time=2.5):
    fig, axs = plt.subplots(len(signals), 1, figsize=(12, 6), sharex=True)
    for ax, signal, label in zip(axs, signals, labels):
        if signal is not None:
            t = signal[:, 0]
            amplitude = signal[:, 1]
            ## Strip 2.5 seconds from start
            mask = t >= strip_time
            t = t[mask]
            amplitude = amplitude[mask]
            ax.plot(t, amplitude, label=label, linewidth=1)
    axs[0].set_title('Time-Domain Signals')
    axs[-1].set_xlabel('Time (s)')
    for ax in axs:
        ax.set_ylabel('Amplitude')
        ax.legend()
        ax.set_ylim(2, 3)
        ax.grid()
    plt.tight_layout()
    plt.savefig('time_domain_signals.png')

plot_time_domain([signal1, signal2, signal3], ['Signal 1', 'Signal 2', 'Signal 3'])

## Compute multiple frequency-domain signals using FFT
def compute_all_fft(signals, strip_time=2.5):
    fsignals = []
    for signal in signals:
        fsignal = compute_fft(signal, strip_time)
        fsignals.append(fsignal)
    return fsignals


def compute_fft(signal, strip_time=2.5):    
    if signal is None:
        return None
    t = signal[:, 0]
    amplitude = signal[:, 1]
    ## Strip 2.5 seconds from start         
    mask = t >= strip_time
    t = t[mask]
    amplitude = amplitude[mask]
    N = len(amplitude)
    T = t[1] - t[0]  # Sampling interval
    ## Compute FFT using pyfftw
    xf = np.fft.rfftfreq(N, T)
    yf = pyfftw.interfaces.numpy_fft.rfft(amplitude)
    return np.column_stack((xf, np.abs(yf)))


## Plot frequency-domain signals
## Limit frequency axis to 0-max_freq Hz
def plot_frequency_domain(fsignals, labels, filename, max_freq=2000):
    fig, axs = plt.subplots(len(fsignals), 1, figsize=(12, 6), sharex=True)
    for ax, signal, label in zip(axs, fsignals, labels):
        if signal is not None:
            xf = signal[:, 0]
            yf = signal[:, 1]
            N = len(yf)
            ## Report 10 highest frequency components in descending order 
            ## and print out their frequency and magnitude.
            ## Ignore the DC component at index 0. 
            ## and frequencies less than 15 Hz apart from previous maximums
            mags = np.abs(yf)
            # indices sorted by magnitude (highest first)
            sorted_idx = np.argsort(mags)[::-1]
            accepted = []
            for j in sorted_idx:
                if j == 0:
                    continue  # ignore DC component
                freq = xf[j]
                # skip if within 15 Hz of any already accepted peak
                if any(abs(freq - xf[k]) < 15.0 for k in accepted):
                    continue
                accepted.append(j)
                if len(accepted) >= 10:
                    break
            print(f"Top {len(accepted)} frequency components for {label}:")
            for i in accepted:
                print(f"Frequency: {xf[i]:.2f} Hz, Magnitude: {mags[i]:.2f}")
            ## Create a filtered yf with only the selected components
            yf_filtered = np.zeros_like(yf)
            if accepted:
                yf_filtered[accepted] = yf[accepted]
            ## Limit frequency axis to 0-max_freq Hz
            freq_mask = xf <= max_freq
            xf = xf[freq_mask]
            yf = yf[freq_mask]
            yf_filtered = yf_filtered[freq_mask]
            ## Plot frequency-domain signal in log scale, add high frequency components with red 
            ax.semilogy(xf, np.abs(yf), label=label, linewidth=1)
            ax.semilogy(xf, np.abs(yf_filtered), label=f"{label} (Filtered)", linewidth=1, color='red') 
    axs[0].set_title('Frequency-Domain Signals')
    axs[-1].set_xlabel('Frequency (Hz)')
    for ax in axs:
        ax.set_ylabel('Magnitude')
        ax.legend()
        ax.grid()
    plt.tight_layout()
    plt.savefig(filename)


[fsignal1, fsignal2, fsignal3] = compute_all_fft([signal1, signal2, signal3])


plot_frequency_domain([fsignal1, fsignal2, fsignal3], ['Signal 1', 'Signal 2', 'Signal 3'], 'frequency_domain_signals.png')

## Do a windowed FFT using a Welch window. Set a center time and a window size.
def windowed_fft(signal, center_time=5.0, window_size=1.0, strip_time=2.5):
    if signal is None:
        return None
    t = signal[:, 0]
    amplitude = signal[:, 1]
    ## Strip 2.5 seconds from start
    mask = t >= strip_time
    t = t[mask]
    amplitude = amplitude[mask]
    ## Select windowed segment
    half_window = window_size / 2
    window_mask = (t >= center_time - half_window) & (t <= center_time + half_window)
    t_window = t[window_mask]
    amplitude_window = amplitude[window_mask]
    N = len(amplitude_window)
    if N < 2:
        return None
    T = t_window[1] - t_window[0]  # Sampling interval
    ## Apply Welch (parabolic) window: w[n] = 1 - ((n - (N-1)/2) / ((N-1)/2))^2
    n = np.arange(N)
    denom = (N - 1) / 2.0
    if denom == 0:
        window = np.ones(N)
    else:
        window = 1.0 - ((n - denom) / denom) ** 2
    ## plot window for verification
    #plt.figure()
    #plt.plot(t_window, window)
    #plt.title('Welch Window')
    #plt.xlabel('Time (s)')
    #plt.ylabel('Amplitude')
    #plt.grid()
    #plt.show()
    amplitude_windowed = amplitude_window * window
    ## Compute FFT using pyfftw
    xf = np.fft.rfftfreq(N, T)
    yf = pyfftw.interfaces.numpy_fft.rfft(amplitude_windowed)
    return np.column_stack((xf, np.abs(yf)))


def windowed_all_fft(signals, center_time=5.0, window_size=1.0, strip_time=2.5):
    fsignals = []
    for signal in signals:
        fsignal = windowed_fft(signal, center_time, window_size, strip_time)
        fsignals.append(fsignal)
    return fsignals


windowed_fsignals = windowed_all_fft([signal1, signal2, signal3], center_time=5.0, window_size=1.0)


plot_frequency_domain(windowed_fsignals, ['Signal 1 Window 5s', 'Signal 2 Window 5s', 'Signal 3 Window 5s'], filename='window_frequency_domain_5s.png')

windowed_fsignals = windowed_all_fft([signal1, signal2, signal3], center_time=3.75, window_size=1.0)


plot_frequency_domain(windowed_fsignals, ['Signal 1 Window 3.75s', 'Signal 2 Window 3.75s', 'Signal 3 Window 3.75s'], filename='window_frequency_domain_3.75s.png')