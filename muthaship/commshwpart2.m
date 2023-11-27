clc
clear
close all

W = 1;
T = 0.25;
A = 1 / T;

f = 0:0.01:4;

Y = A * T * exp((-log(2) / 2) * (f / W).^2 - (1j * pi * f * T)) .* sinc(f * T);

magnitude_Y = abs(Y);

magnitude_Y_dB = 20 * log10(abs(Y));

figure;
plot(f, magnitude_Y_dB);
axis([0 4 -60 0])
xlabel('Frequency (f)');
ylabel('|Y(f)| (dB)');
title('Magnitude Spectrum of Y(f) in Decibels');
grid on;

t = -0.5:0.01:1;

y = A .* qfunc((2*pi*W * (t - T)) / sqrt(log(2)));

figure;
plot(t, y);
xlabel('time (t)');
ylabel('output y(t)');
title('y(t)');
grid on;

