F = imread('cameraman.tif');
C=1;
gamma=(1/1.6);
I=uint8(C.*((double(F)).^gamma));
filter_size=5;
% filter_sigma=5;
filter=fspecial('gaussian', filter_size);
filtered = imfilter(I, filter);

subplot(2, 2, 1); imshow(F); title('Original Image');
subplot(2, 2, 2); imshow(I); title('Transformed Image');
subplot(2, 2, 3); imshow(filtered); title('Smoothed Image');