I = imread('face_image.jpg');
figure,imshow(I);
h = ones(2,2,'uint8');
[x y] = size(I);
img = zeros(x+1, y+1,'uint8');
for i = 1:x
    for j = 1:y
        img(i,j) = I(i,j);
    end
end
for i = 1: x
    for j = 1:y
        img(i,j) = img(i,j)*0.25+img(i+1,j)*0.25+img(i+1,j+1)*0.25+img(i,j+1)*0.25;
    end
end
figure,imshow(img);