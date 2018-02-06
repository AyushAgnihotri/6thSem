I = imread('cameraman.tif');
for row = 8:30
    for column = 15:60
        A(row-7, column-14) = I(row, column);
    end
end
imshow(A);