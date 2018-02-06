I = imread('Lenna.png');
imtool(I);
d  = sqrt((329 - 266)*(329 - 266) + (266 - 266)*(266 - 266))

fprintf('Distance between pupil = %f\n',d);