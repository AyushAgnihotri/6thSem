%clc;
%close all;
%clear all;

F=imread('cameraman.tif');
G=F;

[rows cols]=size(F);

m=input('Enter value of m ');
e=input('Enter value of e ');

 for i=1:rows
    for j=1:cols
        G(i,j)=1/((m/F(i,j))^e);
    end
 end


subplot(2,1,1);
imshow(F);
title('Original image');
subplot(2,1,2);
imshow(G);
title('Result');

 