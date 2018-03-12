I = imread('cameraman.tif');
%h = fspecial('laplacian', 0.2);
[x y] = size(I);
img = zeros(x+2, y+2,'uint8');
for i = 2:x+1
    for j = 2:y+1
        img(i,j) = I(i-1,j-1);
    end
end
for i = 2: x+1
    for j = 2:y+1
        temp = 0;
        for k = -1:1
            for l = -1:1
                temp = temp + (img(i+k,j+l)*h(2+k,2+l))/5;
            end
        end
        img(i,j) = temp;
    end
end
imshow(img);