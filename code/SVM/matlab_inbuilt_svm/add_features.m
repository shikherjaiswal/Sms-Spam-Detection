function [ X ] = add_features(extra_feature_file)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

X = tdfread(extra_feature_file);
X = X.examples;

end