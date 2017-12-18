clc
close all
clear all
%%
% read input and output
X = read_input('super_reduced_examples.txt');
Y = read_output('output.txt');
%%

%X = select_features(X);

%%
% add extra features
X = [X read_input('extra_examples.txt')];
%X = normalize(X);
%%
% NAIVE BAYES CLASSIFIER

disp('--- START NBC---')

%% creating train and test data 
N = size(X,1);

% Running K -fold cross validation
K  = 10;
fold_size  = floor(N/K);

% storing accuracy for train and test set
tr_set = zeros(K,K-1);      
tt_set = zeros(K,K-1);


% storing accuracy for train set , Both spam and ham
tr_spm_set = zeros(K,K-1);
tr_hm_set  = zeros(K,K-1);


% storing accuracy for test set , Both spam and ham
tt_spm_set = zeros(K,K-1);
tt_hm_set  = zeros(K,K-1);

for k = 1:K
    fprintf('Running for %d fold\n',k);
rd = randperm(N);

% for Test data
u = X(rd(1:fold_size),:);
v = Y(rd(1:fold_size),:);

% for Train data
x = X(rd(fold_size+1:end),:);
y = Y(rd(fold_size+1:end),:);

for fold = 1:K-1
    
    fprintf('Taking %d fold number\n ',fold);
    kx = x(1:fold*fold_size,:); 
    ky = y(1:fold*fold_size,:); 

%% Training Data Details
[conf confMat] = NBC(kx,ky,kx,ky);
tot_spam_ham = sum(transpose(confMat));
tr_set(k,fold) =  (conf*100);
tr_spm_set(k,fold) = (confMat(2,2)*100)/tot_spam_ham(1,2);
tr_hm_set(k,fold) =(confMat(1,1)*100)/tot_spam_ham(1,1);

%% Testing Data Details
[conf confMat] = NBC(kx,ky,u,v);
tot_spam_ham = sum(transpose(confMat));
tt_set(k,fold)  = (conf*100);
tt_spm_set(k,fold) = (confMat(2,2)*100)/tot_spam_ham(1,2);
tt_hm_set(k,fold) = (confMat(1,1)*100)/tot_spam_ham(1,1) ;

end    % end of each fold loop 

end    % end of K fold loop

 tr = sum(tr_set)./K;
 tt = sum(tt_set)./K;
tr_spm = sum(tr_spm_set)./(K);
tr_hm  = sum(tr_hm_set)./(K);
tt_spm = sum(tt_spm_set)./(K);
tt_hm = sum(tt_hm_set)./(K);

figure;

xaxis  = 1:K-1-1;
xaxis = xaxis.*fold_size;
plot(xaxis,tr(:,1:K-2),'-*');
hold on;
plot(xaxis,tt(:,1:K-2),'-x');
hold on;
plot(xaxis,tr_spm(:,1:K-2),'--o');
hold on;
plot(xaxis,tr_hm(:,1:K-2),'--+');
hold on;
plot(xaxis,tt_spm(:,1:K-2),'--o');
hold on;
plot(xaxis,tt_hm(:,1:K-2),'--+');
xlabel('Train Set Size');
ylabel('Accuracy');
title('Naive Bayes Classifier');
legend('Training set classification','Test set classification','Training set Spam classification','Training set Ham classification','Test set Spam classification','Test set Ham classification');