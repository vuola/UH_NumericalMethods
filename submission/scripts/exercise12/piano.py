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
def create_initial_string(l=1.0, n=1000, shape='flat'):
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
    z = x / l
    ## Return as Nx2 array
    return np.column_stack((z, y))


## Create initial string shapes
flat_string = create_initial_string(l=1.0, n=2000, shape='flat')
round_string = create_initial_string(l=1.0, n=2000, shape='round')
gaussian_string = create_initial_string(l=1.0, n=5000, shape='gaussian')



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
    plt.savefig('initial_string_shapes.png')


## test_initial_string_shapes()

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
            xf = signal[:, 0]
            yf = signal[:, 1]
            N = len(yf)
            ## Report k highest frequency components in descending order 
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
                # skip if within r Hz of any already accepted peak
                if any(abs(freq - xf[k]) < r for k in accepted):
                    continue
                accepted.append(j)
                if len(accepted) >= k:
                    break
            print(f"Top {len(accepted)} frequency components for {label}:")
            for i in accepted:
                print(f"Frequency: {xf[i]:.2f} Hz, Magnitude: {mags[i]:.2f}")
            ## Create a filtered yf with only the selected components
            yf_filtered = np.zeros_like(yf)
            if accepted:
                yf_filtered[accepted] = yf[accepted]
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


## Compute FFT of all signals
[flat_f, round_f, gaussian_f] = compute_all_fft([flat_string, round_string, gaussian_string])

## Plot frequency-domain signals
plot_frequency_domain([flat_f, round_f, gaussian_f], 
                      ['Flat Top', 'Rounded Top', 'Gaussian'], 
                      'piano_string_frequency_domain.png', 
                      peaks=[7, 7, 3], res=[35, 35, 500])

