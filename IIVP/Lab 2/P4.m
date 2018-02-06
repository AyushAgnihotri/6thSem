clear max min
I1 = imread('monkey.jpg');
Lenna = imread('Lenna.png');
I2 = rgb2gray(Lenna);

y = imadd(I1,I2);

max1 = max(y(:));
min1 = min(y(:));

fprintf('maximum value %d\n',max1);
fprintf('minimum value %d\n',min1);

imshow(y);