%% for KNN PLOT
tr = [95.76 94.76 91.01 93.50 92.91 91.94];
tr_spm = [77.37 66.53 59.03 54.08 48.32 40.16];
tr_hm  = [98.61 99.12 95.77 99.60 99.81 99.95];
xaxis  = [1 3 5 7 9 11];
figure;
plot(xaxis,tr,'-*');
hold on;

plot(xaxis,tr_spm,'--o');
hold on;
plot(xaxis,tr_hm,'--+');

xlabel('Parameter K for KNN');
ylabel('Accuracy');
title('K-Nearest Neighbour');
legend('Overall Set classification',' Spam Set classification',' Ham Set classification');