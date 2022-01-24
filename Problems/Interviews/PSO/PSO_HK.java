package PSO;

import static PSO.PSOc.generateRandomVal;

public class PSOc {
    //Parameters
    // i variable for x items position
    // j variable for particales
    //Parameters of problem
    public  static double maxInf=60;// - infinty
    public  static int nVar=2; // numer of problem variable
    public  static double varMin=0; //low Bound of decision variable
    public  static double varMax=60;  //upper Bound of decision variable
     //Parameters of PSO
    public  static int maxIt=5; // numeber of itrrartion
    public  static int nPop=2; //Population size- swarm size
    public  static double w=1; // Inertia Coefficient 
    public  static double c1=1; // Personal Acceleration Coefficient
    public  static double c2=1; //social Acceleration Coefficient
    
    public static void main(String[] args) {
        //intialzation
        Problem globalBestPos=new Problem();//generate
        double globalBestCost=globalBestPos.objFunction();

        Particle particles[] =new Particle[nPop];
       
        //generate the population and set globalbestpos and globalbestcost 
        for(int j=0; j<nPop; j++){
            particles[j]=new  Particle();
            if (particles[j].cost<globalBestCost){
                //if cost of this particle is less than the global best one then update current global best particle and cost
                // globalBestPos.setX(particles[j].position.getX());
                globalBestPos.setItem(particles[j].position.getItem(0),0);
                globalBestPos.setItem(particles[j].position.getItem(1),1);
                globalBestCost=particles[j].position.objFunction();
                //update cost too
            }
        }
        System.out.println("globalBest Position :"+globalBestPos.toString());
        System.out.println("globalBest Cost :"+globalBestPos.objFunction());
        // main loop of PSo
        for(int it=0;it<maxIt;it++){
            System.out.println("\t\t\t"+it+" iteration");
            for(int j=0; j<nPop; j++){
                
                System.out.print("Pos = "+particles[j].position.toString()
                    +"--F(x) = "+particles[j].position.objFunction()
                    +" --V(x) = "+particles[j].velocity.toString());
                //calculate V(k+i)
                for(int i=0; i<nVar;i++){
                    double temp=w*generateRandomVal(0.1,1)*particles[j].velocity.getItem(i);
                    temp+=c1*(particles[j].bestPosition.getItem(i)-particles[j].position.getItem(i));
                    temp+=c2*generateRandomVal(0.1,1)*(globalBestPos.getItem(i)-particles[j].position.getItem(i));
                    particles[j].velocity.setItem(temp, i);
                }//end x velocity vector loop 
                
                // System.out.println("globalBest Position 1:"+globalBestPos.toString());
                
                //calculate X(k+1)
                for(int i=0; i<nVar;i++){
                    double temp=particles[j].position.getItem(i)+particles[j].velocity.getItem(i);
                    //temp = Math.abs(temp);
                    //here we used corner bound strategy
                    if(temp>varMax )
                        temp=varMax; // if out max var range
                    if(temp < varMin )
                        temp=varMin;//if out min var range 
                    particles[j].position.setItem(temp, i);
                }//end x position vector loop
                particles[j].cost= particles[j].position.objFunction();

              
                System.out.println(" --V(k+1)= "+particles[j].velocity.toString() 
                    +" --X(k+1)="+particles[j].position.toString());
                if(particles[j].cost<particles[j].bestCost){
                    particles[j].bestPosition.setX(particles[j].position.getX());
                    particles[j].bestCost=particles[j].cost;
                }// end if choose local best
                
            // System.out.println("globalBest Position 2:"+globalBestPos.toString());
                
                if (particles[j].cost<globalBestCost){
                    globalBestPos.setX(particles[j].position.getX());
                    globalBestCost=particles[j].cost;
                    System.out.println("update Gbest");
                } // end if choose global best    
            }//end particles loop
        }// end main loop
        
        System.out.println("globalBest Position :"+globalBestPos.toString());
        System.out.println("globalBest Cost :"+globalBestPos.objFunction());
               
    }// end main program
    
   
    
    public static double generateRandomVal(double min,double  max){
        return Math.floor(Math.random()*(max-min+1)+min); 
            // return (a+Math.random()*(b+1));
    }

}//end  PSOc

class Problem{
    double x[],a,b;
    int n;
    Problem(){
        n=PSOc.nVar;
        a=PSOc.varMin;
        b=PSOc.varMax;
        x=new double[n];
        //generate randomly created variable of position vector within the range a,b
        for(int i=0; i<n;i++)
            x[i]=PSOc.generateRandomVal(a, b);
    }
    double getItem(int index){return x[index];}//get item from the vector
    void setItem(double v,int index){
        x[index]=v;
    }//set item to the vector
    double []getX(){return x;}//get position vector
    void setX(double vet[]){x=vet;}//set position vector
    public String toString(){//convert it to string
        String s="";
        for(int i=0; i<n;i++)
            s+=""+x[i]+",";
        return s;
    }
    public double objFunction(){//fitness function
        double sum=0;
        for(int i=0; i<n;i++){
            sum+=x[i];//for sphere x[i]*x[i] and return the sum as is
        }
        return (sum/n);
    }
}//end problem
class Particle{
    //for each particle it will contain 
    //position vector
    //randomly generated velocity
    //cost is the fitness of each position particle i think
    //Pbest
    //f best
    public Problem position;
    Problem velocity;
    double cost;
    Problem bestPosition;
    double bestCost;
    Particle(){
        double v[]=new double[PSOc.nVar];
    
        for (int i = 0; i < PSOc.nVar; i++) {
            v[i]=0;
        } // zero vector

        position=new Problem();
        velocity=new Problem();
        bestPosition=new Problem();
        bestPosition.setX(position.getX());//set best position with zero vector for first iteration
        cost=position.objFunction();
        bestCost=bestPosition.objFunction();
    }
} // end particle
