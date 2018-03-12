I = imread('cameraman.tif');
h = fspecial('gaussian', [5 5], 1);
[x y] = size(I);
img = zeros(x+4, y+4,'uint8');
for i = 3:x+2
    for j = 3:y+2
        img(i,j) = I(i-2,j-2);
    end
end
for i = 3: x+2
    for j = 3:y+2
        temp = 0;
        for k = -2:2
            for l = -2:2
                temp = temp + img(i+k,j+l)*h(3+k,3+l);
            end
        end
        img(i,j) = temp;
    end
end
imshow(img);