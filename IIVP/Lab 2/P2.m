min = 255;
max = 0;

grayLenna = rgb2gray(I);

for i = 1:512
    for j = 1:512
        if (grayLenna(i,j) < min)
            min = grayLenna(i,j);
        end
        if (grayLenna(i,j) > max)
            max = grayLenna(i,j);
        end
    end
end

fprintf('Maximum value is %d\n', max);
fprintf('Minimum value is %d\n', min);

scaledGrayLenna = grayLenna;

for i = 1:512
    for j = 1:512
        scaledGrayLenna(i,j) = (scaledGrayLenna(i,j) - min) * (255/(max - min));
    end
end

imshow(scaledGrayLenna);
