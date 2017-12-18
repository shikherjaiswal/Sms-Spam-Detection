clc
clear

%% read input and output
X = read_input('super_reduced_examples.txt');
Y = read_output('output.txt');

%% select features

% X = select_features(X);

%% add extra features
X = [X read_input('extra_examples.txt')];
%X = X(1:1000,:);
%Y = Y(1:1000,:);

[mx, nx] = size(X);

%% shuffle data
%rng(1);
perm = randperm(mx);
X = X(perm,:);
Y = Y(perm,:);

%% separate training and test data
% frac = 0.7;
% test_X = X(ceil(frac*mx)+1:end,:);
% test_Y = X(ceil(frac*mx)+1:end,:);
% X = X(1:ceil(frac*mx),:);
% Y = Y(1:ceil(frac*mx),:);

k = 1;
%% k-fold cross validation
[mx, nx] = size(X);
folds = 10;
s = mx / folds;
error = zeros(folds,1);

Confusion_M = zeros(2,2);
for i=1:folds
    fprintf('fold %d / %d',i,folds);
    valid_ind = ceil((i-1)*s) + 1 : ceil(i*s);
    train_ind = 1:mx;
    train_ind(valid_ind) = [];
    valid_X = X(valid_ind,:);
    train_X = X(train_ind,:);
    
    valid_Y = Y(valid_ind,:);
    train_Y = Y(train_ind,:);
    
    train_mean = mean(train_X);
    train_var = var(train_X);
   
    train_X = standardize(train_X, train_mean, train_var);
    valid_X = standardize(valid_X, train_mean, train_var);
    
    predicted_valid_Y = knn_fun(train_X, train_Y, valid_X, k);
    
    conf = conf_matrix(valid_Y, predicted_valid_Y);
    Confusion_M = Confusion_M + conf;
    
end

%% average error of all folds
hams = Confusion_M(1,1) + Confusion_M(1,2);
spams = Confusion_M(2,1) + Confusion_M(2,2);
hams_blocked = ( Confusion_M(1,2) ) * 100 / hams;
spams_caught = ( Confusion_M(2,2) ) * 100 / spams;
accuracy = ( Confusion_M(1,2) + Confusion_M(2,1) ) * 100 / ( hams + spams ); 


