import numpy as np
from timeit import default_timer as timer

def Poisson(T_n,T_o,S,nx,ny,dx,dy,epsil_p):
    
    steps = int(0)
    
    while(1):
        
        sum_error = np.zeros([1],dtype = np.float64)

        
        T_n[1:nx-1,1:ny-1,:,:] = (T_o[0:nx-2,1:ny-1,:,:] + T_o[2:nx,1:ny-1,:,:] + T_o[1:nx-1,0:ny-2,:,:] + T_o[1:nx-1,2:ny,:,:]                                  - dx**2*S[1:nx-1,1:ny-1,:,:])/4.0
    
        sum_error[:] = np.sum(abs(T_n[1:nx-1,1:ny-1] - T_o[1:nx-1,1:ny-1]))/((nx-1)*(ny-1))
        
        T_o[1:nx-1,1:ny-1]= T_n[1:nx-1,1:ny-1]
        
        if (sum_error<epsil_p):
            break
            
        steps = steps+1
        
    return T_o, steps



def main():
    
    #grids shape
    nx = 64; ny = 64
    
    #---------------------- Define variables ---------------------#
    #Dfine 2-D velocity
    T_o = np.zeros([nx,ny,1,1], dtype = np.float64)
    T_n = np.zeros([nx,ny,1,1], dtype = np.float64)
    
    S = np.zeros([nx,ny,1,1], dtype = np.float64)
    #-------------------------------------------------------------#    
    
    # Simulation parameter
    Re = 100
    dt = 1/2500
    t_real =  int(0)
    epsil_p = 10**(-12)

    #simulation factor
    x_len = 1.0; y_len = 1.0
    
    x = np.zeros([nx,1,1,1], dtype = np.float64)
    y = np.zeros([1,ny,1,1], dtype = np.float64)
    
    dx = x_len/(nx-1); dy = y_len/(ny-1) #delta panel 칸의 갯수로 나눠줘야함
    x0 = 0.0; y0 = 0.0
    xf = 1.0; yf = 1.0
    
    alpha = 1.0
    
    #uniform grids
    x[:,0,0,0] = np.linspace(x0,xf,nx)
    y[0,:,0,0] = np.linspace(y0,yf,ny)
    
    S = np.sin(np.pi*x)*np.sin(np.pi*y)
    
    start = timer()
    #Poisson euqation 
    T_o, steps = Poisson(T_n,T_o,S,nx,ny,dx,dy,epsil_p)
    
    duration = timer() - start
    
    print(duration)

    #print contour stream line & velocity field
    contour = open('Heat Poisson.plt', 'w')

    contour.write('VARIABLES = "x","y","T"\n')
    contour.write('Zone T="HIT%d"\n'%0)
    contour.write('I=%d J=%d\n' %(nx, ny))
    
    for j in range(0, ny):
        for i in range(0, nx):
            contour.write('%.5f %.5f %.5f\n' %(i,j, T_o[i,j,0,0]))
    
    contour.close()
    
if __name__ == "__main__":
        
    main()
        
    print("All process is finished!")
