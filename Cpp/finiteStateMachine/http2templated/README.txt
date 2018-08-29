
   http2 state machine implementatio explained.
   =============================================

   one of the purposes of the state machine is that addData2Stream() 
   would know to which member of the stream it should add the data 

      ------------------------
         http2 stream 
      ------------------------
      buffer request header 
      buffer request body 
      buffer response header
      buffer response body         
      ------------------------

   to achieve this we put to use two cpp strategies 
      *  state design pattern 
      *  cpp traits 
      
   the state machine class is templated with SIDE class 
      template<class SIDE>
      class Http2Fsm
      {
         Http2State<SIDE> *current_
         ...   
      };

   the SIDE template parameter affects the instantiation of the current state.
   the arguments it can receive are ClientSide and ServerSide
   which are declared like so : 
      typedef struct ClientSide ClientSide;      
      typedef struct ServerSide ServerSide;
            
   since its only a typedef the compiler does not demand decleration of these structs 
   but it does let you pass them as arguments 
   so instantiating a client state machine would be 
      Http2Fsm<ClientSide> clientFsm;
   and instantiating a server state machien would be 
      Http2Fsm<ServerSide> serverFsm;

   the client fsm instantiation would use the following class version
      class Http2Fsm
      {
         Http2State<ClientSide> *current_
      }
