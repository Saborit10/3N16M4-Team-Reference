// Desarreglos

ds[0] = 1;
ds[1] = 0;
ds[i] = ( ds[i-1] + ds[i-2] ) * (i-1);
