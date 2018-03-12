clear;
clc;
Img = imread('cameraman.tif');
b1 = double(bitget(Img,1));
subplot(4,2,1);
imshow(b1);
title('Bitplane-1');

b2 = double(bitget(Img,2));
subplot(4,2,2);
imshow(b2);
title('Bitplane-2');

b3 = double(bitget(Img,3));
subplot(4,2,3);
imshow(b3);
title('Bitplane-3');

b4 = double(bitget(Img,4));
subplot(4,2,4);
imshow(b4);
title('Bitplane-4');

b5 = double(bitget(Img,5));
subplot(4,2,5);
imshow(b5);
title('Bitplane-5');

b6 = double(bitget(Img,6));
subplot(4,2,6);
imshow(b6);
title('Bitplane-6');

b7 = double(bitget(Img,7));
subplot(4,2,7);
imshow(b7);
title('Bitplane-7');

b8 = double(bitget(Img,8));
subplot(4,2,8);
imshow(b8);
title('Bitplane-8');

cat = b1+(2*b2)+(4*b3)+(8*b4)+(16*b5)+(32*b6)+(64*b7)+(128*b8);
figure;
imshow(uint8(cat));
title('Reconstructed');