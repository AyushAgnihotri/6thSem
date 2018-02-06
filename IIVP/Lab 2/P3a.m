newScaled50 = scaledGrayLenna;

for i = 1:512
    for j = 1:512
        o = intensity_change_50(newScaled50(i,j));
        newScaled50(i,j) = o;
    end
end

imshow(newScaled50)