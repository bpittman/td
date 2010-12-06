./td > serial_out.txt
mpirun -np 2 tdmpi > 2_out.txt
mpirun -np 4 tdmpi > 4_out.txt
mpirun -np 8 tdmpi > 8_out.txt
mpirun -np 16 tdmpi > 16_out.txt
