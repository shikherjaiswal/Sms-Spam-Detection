function [ Y ] = read_output( out_file )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

Y = tdfread(out_file);
Y = Y.output;

end