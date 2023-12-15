#include <EloquentTinyML.h>
#include <eloquent_tinyml/tensorflow.h>

#include "net.h" // network weights
//#include "testdata.h" // test data

#define N_INPUTS 64
#define N_OUTPUTS 7
// in your projects you may need to tweak this value: it's a trial and error process
#define TENSOR_ARENA_SIZE 30 * 1024

Eloquent::TinyML::TensorFlow::TensorFlow<N_INPUTS, N_OUTPUTS, TENSOR_ARENA_SIZE> tf;

void setup() {
    Serial.begin(9600);
    tf.begin(model);
}


void loop() {


    // check if model loaded fine
    /*if (!tf.isOk()) {
        Serial.print("ERROR: ");
        Serial.println(tf.getErrorMessage());
        //while (true) delay(1000);
    }*/
    
    float x_test[1024] = {0};
    float y_pred[2] = {0};
    int j = 0;

    float my_test[64] = {
        15, 12, 15,  2,  4, 15, 15,  3,  1,  8,  4,  5,  7,  2, 12, 11, 12,
        6, 15, 15,  2,  0, 11,  5, 15,  1,  8,  4,  7,  2,  5,  7, 10, 10,
        3,  1,  6, 13,  6,  0, 11,  2, 11,  9, 10,  1,  1,  9,  5,  7,  2,
        1,  6,  5,  7,  3,  5,  3,  1,  2, 15,  8, 10,  0
    };
    float my_pred[7] = {0};

    //uint32_t start = micros();
    tf.predict(my_test, my_pred);
    //uint32_t timeit = micros() - start;
    Serial.println(tf.probaToClass(my_pred));

    Serial.println(strtol("ff", 0, 16));
    
    delay(2000);
    
    /*for (j=0; j < 40; j=j+1)
    {

      for(int i = 0; i < N_INPUTS; i++)
        {x_test[i] = x_test_cut[j][i];  }
    

      uint32_t start = micros();
  
      tf.predict(x_test, y_pred);
  
      uint32_t timeit = micros() - start;
  

      //Serial.print("Predicted proba are: ");  
      //for (int i = 0; i < 2; i++) {
      //    Serial.print(y_pred[i]);
      //    Serial.print(i == 1 ? '\n' : ',');
      //}
  

      Serial.print(j+1);
      Serial.print("\t");
      Serial.print(tf.probaToClass(y_pred));
      Serial.print("\t");
      Serial.print(timeit/1240000.0);
      Serial.print("\n");

  
      delay(1000);
    }
    */
}
