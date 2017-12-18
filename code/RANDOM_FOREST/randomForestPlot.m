%% for Random Forest PLOT
tr = [99.4 99.64 99.64 99.70 99.70];
tr_spm = [96.65 97.12 97.12 97.60 97.60];
tr_hm  = [99.79 100 100 100 100];

tt = [94.07 95.86 95.74 96.94 96.70];
tt_spm = [72.99 73.41 71.30 78.48 76.79];
tt_hm = [97.55 99.58 99.79 100 100];

xaxis  = [1 5 10 15 20];

plot(xaxis,tr,'-*');
hold on;
plot(xaxis,tt,'-x');
hold on;
plot(xaxis,tr_spm,'--o');
hold on;
plot(xaxis,tr_hm,'--+');
hold on;
plot(xaxis,tt_spm,'--o');
hold on;
plot(xaxis,tt_hm,'--+');
xlabel('Forest Size');
ylabel('Accuracy');
title('Random Forests');
legend('Training set classification','Test set classification','Training set Spam classification','Training set Ham classification','Test set Spam classification','Test set Ham classification');