

   thread function for pthread_create() cannot be a member function
   ================================================================

You can't do it the way you've written it because C++ class member functions have a hidden this parameter passed in. 
pthread_create() has no idea what value of this to use, so if you try to get around the compiler by casting the method to a   
function pointer of the appropriate type, you'll get a segmetnation fault. 
You have to use a static class method (which has no this parameter), or a plain ordinary function to bootstrap the class:

class C
{
   public:
      void *hello(void)
      {
         std::cout << "Hello, world!" << std::endl;
         return 0;
      }

   static void *hello_helper(void *context)
   {
      return ((C *)context)->hello();
   }
};
...
C c;
pthread_t t;
pthread_create(&t, NULL, &C::hello_helper, &c);


=========u



My favorite way to handle a thread is to encapsulate it inside a C++ object. Here's an example:

class MyThreadClass
{
   public:
      MyThreadClass() {/* empty */}
      virtual ~MyThreadClass() {/* empty */}

      /** Returns true if the thread was successfully started, false if there was an error starting the thread */
      bool StartInternalThread()
      {
         return (pthread_create(&_thread, NULL, InternalThreadEntryFunc, this) == 0);
      }

      /** Will not return until the internal thread has exited. */
      void WaitForInternalThreadToExit()
      {
         (void) pthread_join(_thread, NULL);
      }

   protected:
      /** Implement this method in your subclass with the code you want your thread to run. */
      virtual void InternalThreadEntry() = 0;

   private:
      static void * InternalThreadEntryFunc(void * This) {((MyThreadClass *)This)->InternalThreadEntry(); return NULL;}

      pthread_t _thread;
};

To use it, you would just create a subclass of MyThreadClass with the InternalThreadEntry() 
method implemented to contain your thread's event loop. You'd need to call WaitForInternalThreadToExit() on the 
thread object before deleting the thread object, of course (and have some mechanism to 
make sure the thread actually exits, otherwise WaitForInternalThreadToExit() would never return)



