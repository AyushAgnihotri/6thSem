I = imread('pout.tif');
figure,imshow(I);

[Gx,Gy] = imgradientxy(I,'sobel');
figure,imshow(Gx);
figure,imshow(Gy);
[magnitude,direction] = imgradient(I,'sobel');

direction = round(direction,45);

figure,imshow(direction);