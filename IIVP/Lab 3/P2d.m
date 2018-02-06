F = imread('cameraman.tif');
% imshow(F);
filter_size=50;
% filter_sigma=5;
filter=fspecial('gaussian', filter_size);
filtered = imfilter(F, filter);
imshow(filtered);

subplot(2, 2, 1); imshow(F); title('Original Image');
subplot(2, 2, 2); imshow(filtered); title('Smoothed Image');