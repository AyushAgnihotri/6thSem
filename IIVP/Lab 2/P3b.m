newScaled20 = scaledGrayLenna;

for i = 1:512
    for j = 1:512
        o = intensity_change_20(newScaled50(i,j));
        newScaled20(i,j) = o;
    end
end

figure,imshow(newScaled20)