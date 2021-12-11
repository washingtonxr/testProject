close all;
clear all;
M = 4;         % Modulation order for QPSK
nSym = 50000;   % Number of symbols in a packet
sps = 4;       % Samples per symbol
timingErr = 2; % Samples of timing error
snr = 15;      % Signal-to-noise ratio (dB)

txfilter = comm.RaisedCosineTransmitFilter(...
    'OutputSamplesPerSymbol',sps);
rxfilter = comm.RaisedCosineReceiveFilter(...
    'InputSamplesPerSymbol',sps,'DecimationFactor',2);

symbolSync = comm.SymbolSynchronizer;

data = randi([0 M-1],nSym,1);
modSig = pskmod(data,M,pi/4);
txSig = txfilter(modSig);

%******************** 整数倍采样偏差 即相差整数个采样点
fixedDelay = dsp.Delay(timingErr);
fixedDelaySym = ceil(fixedDelay.Length/sps); % Round fixed delay to nearest integer in symbols
delayedSig = fixedDelay(txSig);
% 
% % delayedSig_temp1 = [zeros(timingErr,1);txSig(1:end-timingErr,1)];
% % 结论：误码率为0 

%******************** 小数倍采样偏差（对应采样相差） 即相差小数个采样点
varDelay = dsp.VariableFractionalDelay;
k = 16/15;
txDelay = varDelay(txSig,k);  
fixedDelaySym = ceil(k/sps); % Round fixed delay to nearest integer in symbols

%******************** 采样频差
% sps_offset = 0.1;
% sps_temp = sps + 0.1;
% time1 = (sps/sps_temp).*(1:length(txSig));
% txSig_temp = interp1((1:length(txSig))',txSig,time1','spline');

% txSig_temp2 = resample(txSig,sps*10,sps_temp*10);

rxSig = awgn(txDelay,snr,'measured');
rxSample = rxfilter(rxSig);
% scatterplot(rxSample(1001:end),2);

scatterplot(rxSample(1001:end),2);

rxSync = symbolSync(rxSample);
scatterplot(rxSync(1001:end),2)

recData = pskdemod(rxSync,M,pi/4);
sysDelay = dsp.Delay(fixedDelaySym + txfilter.FilterSpanInSymbols/2 + ...
    rxfilter.FilterSpanInSymbols/2);

recData2 = recData(sysDelay.Length+1:end,1);

[numErr1,ber1] = biterr(data(1:length(recData2),1),recData2);
