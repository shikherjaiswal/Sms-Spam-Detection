clc
close all
clear all
%%
% read input and output
X = read_input('super_reduced_examples.txt');
Y = read_output('output.txt');
Y(Y==0) = -1;
%%

%X = select_features(X);

%%
% add extra features
X = [X read_input('extra_examples.txt')];
%X = normalize(X);
%% SVM
disp('--- START SVM ---')

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

%% Training the model 
    model = fitcsvm(kx,ky,'Standardize',true,'ClassNames',[-1,1]);
  
%% Training Data Details

trX_size = size(kx,1); 
ky_predict = zeros(trX_size,1);

for i = 1:trX_size
    [label,~] = predict(model,kx(i,:));
    ky_predict(i) = label;
end

[conf,confMat] = conf_matrix(ky,ky_predict);
tot_spam_ham = sum(transpose(confMat));
tr_set(k,fold) =  (conf*100);
tr_spm_set(k,fold) = (confMat(2,2)*100)/tot_spam_ham(1,2);
tr_hm_set(k,fold) =(confMat(1,1)*100)/tot_spam_ham(1,1);

%% Testing Data Details
tstX_size = size(u,1); 
v_predict = zeros(tstX_size,1);

for i = 1:tstX_size
    [label,~] = predict(model,u(i,:));
    v_predict(i) = label;
end

[conf, confMat] = conf_matrix(v,v_predict);

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
title('Support Vector Machine');
legend('Training set classification','Test set classification','Training set Spam classification','Training set Ham classification','Test set Spam classification','Test set Ham classification');