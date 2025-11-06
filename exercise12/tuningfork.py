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
def plot_time_domain(signals, labels):
    fig, axs = plt.subplots(len(signals), 1, figsize=(12, 6), sharex=True)
    for ax, signal, label in zip(axs, signals, labels):
        if signal is not None:
            t = signal[:, 0]
            amplitude = signal[:, 1]
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

## Compute and plot frequency-domain signals using FFT
## Strip away strip_time seconds from start
## Limit frequency axis to 0-max_freq Hz

def plot_frequency_domain(signals, labels, strip_time=2.5, max_freq=2000):
    fig, axs = plt.subplots(len(signals), 1, figsize=(12, 6), sharex=True)
    for ax, signal, label in zip(axs, signals, labels):
        if signal is not None:
            t = signal[:, 0]
            amplitude = signal[:, 1]
            ## Strip 2.5 seconds from start
            mask = t >= strip_time
            t = t[mask]
            amplitude = amplitude[mask]
            N = len(amplitude)
            T = t[1] - t[0]  # Sampling interval
            ## Report Nyquist frequency
            nyquist_freq = 0.5 / T
            print(f"Nyquist frequency for {label}: {nyquist_freq:.2f} Hz")
            ## Compute FFT using pyfftw
            xf = np.fft.rfftfreq(N, T)
            yf = pyfftw.interfaces.numpy_fft.rfft(amplitude)
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
    plt.savefig('frequency_domain_signals.png')


plot_frequency_domain([signal1, signal2, signal3], ['Signal 1', 'Signal 2', 'Signal 3'])

## Do a windowed FFT using a Welch window. Slice the time series into two parts using given splitting time and plot the two parts with different colours on the same graph.
def plot_windowed_fft(signals, labels, window_size=2048, overlap=1024, max_freq=2000):
    fig, axs = plt.subplots(len(signals), 1, figsize=(12, 6), sharex=True)
    for ax, signal, label in zip(axs, signals, labels):
        if signal is not None:
            t = signal[:, 0]
            amplitude = signal[:, 1]
            ## Strip 2.5 seconds from start
            mask = t >= 2.5
            t = t[mask]
            amplitude = amplitude[mask]
            N = len(amplitude)
            T = t[1] - t[0]  # Sampling interval
            ## Compute windowed FFT using Welch method
            from scipy.signal import welch
            # adjust nperseg and noverlap to not exceed the available data length
            nperseg = min(window_size, max(1, N))
            noverlap = min(overlap, max(0, nperseg - 1))
            freqs, psd = welch(amplitude, fs=1/T, window='hann', nperseg=nperseg, noverlap=noverlap)
            ## Limit frequency axis to 0-max_freq Hz
            freq_mask = freqs <= max_freq
            freqs = freqs[freq_mask]
            psd = psd[freq_mask]
            ## Plot windowed FFT in log scale
            ax.semilogy(freqs, psd, label=label, linewidth=1)
    # use the figure object so it is accessed (avoids unused-variable warning)
    fig.suptitle('Windowed FFT (Welch Method)')
    axs[-1].set_xlabel('Frequency (Hz)')
    for ax in axs:
        ax.set_ylabel('Power Spectral Density')
        ax.legend()
        ax.grid()
    fig.tight_layout()
    fig.savefig('windowed_fft_signals.png')


plot_windowed_fft([signal1, signal2, signal3], ['Signal 1', 'Signal 2', 'Signal 3'])