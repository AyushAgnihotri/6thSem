F = imread('cameraman.tif');
G = 255-F;
filter_size=5;
% filter_sigma=5;
filter=fspecial('gaussian', filter_size);
filtered = imfilter(G, filter);


subplot(2, 2, 1); imshow(F); title('Original Image');
subplot(2, 2, 2); imshow(G); title('Transformed Image');
subplot(2, 2, 3); imshow(filtered); title('Smoothed Image');