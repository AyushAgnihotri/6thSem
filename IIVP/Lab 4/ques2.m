I = imread('cameraman.tif');
[r,c] = size(I);
I2 = uint8(zeros(r,c));
for i = 1:1:r
    for j = 1:1:c
        if I(i,j) < 70
            I2(i,j) = I(i,j);
        else
            I2(i,j) = 255;
        end
    end
end
subplot(1,3,1),imshow(I);
subplot(1,3,2),imshow((I2));
I3 = I;
for i = 1:1:r
    for j = 1:1:r
        if I2(i,j) ~= 255
            I3(i,j) = I3(i,j)+50;
        end
    end
end
subplot(1,3,3),imshow(I3);
%plot(I3);