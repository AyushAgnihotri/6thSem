I = imread('cameraman.tif');

G = zeros(5,5);
for i=1:1:5
    for j=1:1:5
        d = exp(-1.0*(i*i+j*j)/(2*2*2));
        G(i,j) = d/(2*pi*2*2.0);
    end
end
G=fspecial('gaussian',[5,5],2);
A = ones(5,5) / 25;


I=im2double(I);
I1=imfilter(I,G,'conv');
figure,imshow(I);
figure,imshow(I1);

[x,y] =size(I);

%MASK
for i =1:1:x
    for j=1:1:y
        M(i,j) = I(i,j)-I1(i,j);
    end
end

%High Boost Filtering;
k = 5.7;
for i =1:1:x
    for j=1:1:y
        O(i,j) = I(i,j)+k*M(i,j);
    end
end


figure,imshow(O);