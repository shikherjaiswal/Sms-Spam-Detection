function [ X ] = read_input( inp_file )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

X = tdfread(inp_file);
X = X.examples;

end