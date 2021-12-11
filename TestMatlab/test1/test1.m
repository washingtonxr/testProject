close all;
clear all;
M = 4;         % Modulation order for QPSK
nSym = 50000;   % Number of symbols in a packet
sps = 4;       % Samples per symbol
spsSync = 2;      % Samples per symbol for synchronizers
snr = 15;      % Signal-to-noise ratio (dB)

txfilter = comm.RaisedCosineTransmitFilter(...
    'OutputSamplesPerSymbol',sps);
rxfilter = comm.RaisedCosineReceiveFilter(...
    'InputSamplesPerSymbol',sps,'DecimationFactor',2);
carrierSync = comm.CarrierSynchronizer('SamplesPerSymbol',spsSync);

data = randi([0 M-1],nSym,1);
modSig = pskmod(data,M,pi/4);
txSig = txfilter(modSig);

% temp = 1;  %无相差

temp = exp(1j*pi/6).';  %只有相差

% time = 0:length(txSig)-1;
% temp = exp(1j*2*pi*100.*time/1e6+1j*(pi/6)).';  %有载波偏差和相位偏差

txDoppler_temp1 = txSig.*temp;

rxSig = awgn(txDoppler_temp1,snr,'measured');
rxSample = rxfilter(rxSig);
scatterplot(rxSample(1001:end),2);
% scatterplot(rxSample(1001+1:end),2);  %有定时偏差，即没有找到最佳采样点

rxCorr = carrierSync(rxSample); 
scatterplot(rxCorr(1001:end),2)


rxCorr2 = rxCorr(1:2:end,1);

recData = pskdemod(rxCorr2,M,pi/4);

sysDelay = dsp.Delay(txfilter.FilterSpanInSymbols/2 + ...
    rxfilter.FilterSpanInSymbols/2);

recData2 = recData(sysDelay.Length+1:end,1);

[numErr1,ber1] = biterr(data(1:length(recData2),1),recData2);