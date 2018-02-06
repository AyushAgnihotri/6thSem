clear;
clc;
F=imread('Lenna.png');
subplot(2,4,1);       
imshow(F);
title('Original');

gray = rgb2gray(F);
subplot(2,4,2);
imshow(gray);
title('Gray scale');

G=255-F;
subplot(2,4,3);
imshow(G);
title('Negative');

H=1.*F;
subplot(2,4,4);
imshow(H);
title('Identity');

c = 10;
L=uint8(c.*log(double(1+F)));
subplot(2,4,5);
imshow(L);
title('Logarithmic');

%inv_L = uint8((exp(double(F)) .^ (log(256) / (256-1))) - 1);
%subplot(2,4,6);
%imshow(inv_L);
%title('Inverse Logarithmic');

inv_L = uint8((exp(double(L./c))) - 1);
subplot(2,4,6);
imshow(inv_L);
title('Inverse Logarithmic');

C=1;
gamma=1.2;
I=uint8(C.*((double(F)).^gamma)); %formula for nth power
subplot(2,4,7);
imshow(I);
title('nth power');

J=uint8(C.*((double(F)).^(1/gamma))); %formula for nth root
subplot(2,4,8);
imshow(J);
title('nth root');

