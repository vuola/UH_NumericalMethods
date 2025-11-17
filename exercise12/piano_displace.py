import pyfftw
import numpy as np
import matplotlib.pyplot as plt


## Create a spatial representation of a piano string in its initial state
## when the key is deforming the string most. 
## Parameters:
## l - length of the string (m)
## n - number of spatial points along the string
## w - width of the initial deformation (m)
## A - height of the initial deformation (m)
## shape - shape of the initial deformation:
##        'flat' - flat topped y(x) = A for |x| <= w/2, 0 elsewhere
##        'round' - rounded y(x) = sqrt(w^2 - x^2) for |x| <= w/2, 0 elsewhere
##        'gaussian' - gaussian y(x) = A * exp(-(4*ln(2)*x^2)/w^2) for x in [-l/2, l/2]
## d - central position of the hammer in the x-axis (m). Value between -l/2 and l/2
def create_initial_string(l=1.0, n=1000, shape='flat', d=0.0):
    w = l / 50  # width of initial deformation
    A = 1 # height of initial deformation
    ## Create spatial grid
    x = np.linspace(-l/2, l/2, n)
    ## Create initial deformation
    y = np.zeros_like(x)
    if shape == 'flat':
        y[np.abs(x) <= w/2] = A
    elif shape == 'round':
        mask = np.abs(x) <= w/2
        y[mask] = np.sqrt((w/2)**2 - x[mask]**2)
    elif shape == 'gaussian':
        y = A * np.exp(-(4 * np.log(2) * x**2) / w**2)
    else:
        raise ValueError("Invalid shape. Choose from 'flat', 'round', or 'gaussian'.")
    ## Switch into dimensionless units z = x / l
    z = (x - d) / l
    
    ## Return as Nx2 array
    return np.column_stack((z, y))


## Create initial string shapes
flat_string = create_initial_string(l=1.0, n=1000, shape='flat', d=-0.4)
round_string = create_initial_string(l=1.0, n=1000, shape='round', d=0.4)
gaussian_string = create_initial_string(l=1.0, n=1000, shape='gaussian', d=-0.3)



def test_initial_string_shapes():
    ## Plot all initial string shapes in a stacked plot
    plt.figure(figsize=(10, 10))
    plt.subplot(3, 1, 1)
    plt.plot(flat_string[:, 0], flat_string[:, 1])
    plt.title('Initial Deformation of Piano String - Flat Top')
    plt.ylabel('Displacement (y)')
    plt.grid()  
    plt.subplot(3, 1, 2)
    plt.plot(round_string[:, 0], round_string[:, 1])
    plt.title('Initial Deformation of Piano String - Rounded Top')
    plt.ylabel('Displacement (y)')
    plt.grid()
    plt.subplot(3, 1, 3)
    plt.plot(gaussian_string[:, 0], gaussian_string[:, 1])
    plt.title('Initial Deformation of Piano String - Gaussian')
    plt.ylabel('Displacement (y)')
    plt.grid()
    plt.savefig('displaced_string_shapes.png')


test_initial_string_shapes()

## Compute multiple frequency-domain signals using FFT
def compute_all_fft(signals):
    fsignals = []
    for signal in signals:
        fsignal = compute_fft(signal)
        fsignals.append(fsignal)
    return fsignals


def compute_fft(signal):    
    if signal is None:
        return None
    t = signal[:, 0]
    amplitude = signal[:, 1]
    N = len(amplitude)
    T = t[1] - t[0]  # Sampling interval
    ## Compute FFT using pyfftw
    xf = np.fft.rfftfreq(N, T)
    yf = pyfftw.interfaces.numpy_fft.rfft(amplitude)
    return np.column_stack((xf, np.abs(yf)))


## Plot frequency-domain signals
def plot_frequency_domain(fsignals, labels, filename, peaks, res):
    fig, axs = plt.subplots(len(fsignals), 1, figsize=(12, 6), sharex=True)
    for ax, signal, label, k, r in zip(axs, fsignals, labels, peaks, res):
        if signal is not None:
            ## Detect principal frequencies
            principal_freqs = detect_principal_frequencies(signal, k=k, res=r)

            ## Find matching magnitudes
            magnitudes = []
            for pf in principal_freqs:
                idx = np.argmin(np.abs(signal[:, 0] - pf))
                magnitudes.append(signal[idx, 1])

            ## Print principal frequencies and their magnitudes with 1 decimal place
            print(f'Principal frequencies for {label}: {[f"{pf:.1f}" for pf in principal_freqs]}')
            ## Use scientific notation for magnitudes
            print(f'Magnitudes for {label}: {[f"{mag:.1e}" for mag in magnitudes]}')

            ## Plot intensity spectrum |F(f)|^2
            xf = signal[:, 0]
            yf = np.abs(signal[:, 1])**2
            ax.semilogy(xf, yf, label=label, linewidth=1)

            ## Mark principal frequencies
            for pf in principal_freqs:
                ax.axvline(pf, color='r', linestyle='--', alpha=0.7)
                ax.text(pf, ax.get_ylim()[1]*0.5, f'{pf:.2f} Hz', rotation=90, color='r', fontsize=8,
                        verticalalignment='top', horizontalalignment='right')
    axs[0].set_title('Frequency-Domain Signals')
    axs[-1].set_xlabel('Frequency (Hz)')
    for ax in axs:
        ax.set_ylabel('Magnitude')
        ax.legend()
        ax.grid()
    plt.tight_layout()
    plt.savefig(filename)


## Walk through the frequency spectrum and list an alternating sequence of local maxima and minima in between.
## Return the k highest local maxima that are at least res Hz apart.
def detect_principal_frequencies(signal, k=5, res=20):
    xf = signal[:, 0]
    yf = signal[:, 1]
    N = len(yf)
    local_maxima = []
    local_minima = []
    for i in range(1, N-1):
        if yf[i] > yf[i-1] and yf[i] > yf[i+1]:
            local_maxima.append((xf[i], yf[i]))
        elif yf[i] < yf[i-1] and yf[i] < yf[i+1]:
            local_minima.append((xf[i], yf[i]))
    # Sort local maxima by magnitude
    local_maxima.sort(key=lambda x: x[1], reverse=True)
    principal_freqs = []
    for freq, mag in local_maxima:
        if all(abs(freq - pf) >= res for pf in principal_freqs):
            principal_freqs.append(freq)
        if len(principal_freqs) >= k:
            break
    return principal_freqs


## Compute FFT of all signals
[flat_f, round_f, gaussian_f] = compute_all_fft([flat_string, round_string, gaussian_string])

## Plot frequency-domain signals
plot_frequency_domain([flat_f, round_f, gaussian_f], 
                      ['Flat Top', 'Rounded Top', 'Gaussian'], 
                      'displaced_hammer_frequency_domain.png', 
                      peaks=[9, 9, 1], res=[20, 20, 20])

