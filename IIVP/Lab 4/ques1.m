I = imread('cameraman.tif');
I2 = I;
I = im2double(I);
r2 = input('Enter r2');
s2 = input('Enter s2');
r3 = input('Enter r3');
s3 = input('Enter s3');
[r,c] = size(I);
for i=1:1:r
    for j = 1:1:c
        if I(i,j) < r2 
            I(i,j) = (s2*I(i,j))/r2;
        elseif I(i,j)< r3
            I(i,j) = ((s3-s2)/(r3-r2))*I(i,j) + s2 - ((s3-s2)/(r3-r2))*r2;
        else
            I(i,j) = ((255-s3)/(255-r3))*I(i,j) + 255 - ((255-s3)/(255-r3))*255;
        end
    end
end

subplot(1,2,1),imshow(I2);
subplot(1,2,2),imshow(im2uint8(I));