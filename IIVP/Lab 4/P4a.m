clc;
clear;
my_image = uint16(imread(pout.tif));
std_of_my_image = double(std(my_image(:)));
var_of_my_image = std_of_my_image^2;
mean_of_my_image = mean(my_image(:));
fprintf('%d',std_of_my_image);