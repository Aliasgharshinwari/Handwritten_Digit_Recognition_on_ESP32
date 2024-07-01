/**
 * Run a TensorFlow model to predict the IRIS dataset
 * For a complete guide, visit
 * https://eloquentarduino.com/tensorflow-lite-esp32
 */
// replace with your own model
// include BEFORE <eloquent_tinyml.h>!
#include "model_softmax.h"
#include "mnist_image_array.h"
// include the runtime specific for your board
// either tflm_esp32 or tflm_cortexm
#include <tflm_esp32.h>
//#include<tflm_cortexm.h>
// now you can include the eloquent tinyml wrapper
#include <eloquent_tinyml.h>

// this is trial-and-error process
// when developing a new model, start with a high value
// (e.g. 10000), then decrease until the model stops
// working as expected
#define ARENA_SIZE 10000

Eloquent::TF::Sequential<TF_NUM_OPS, ARENA_SIZE> tf;

void setup() {
    Serial.begin(115200);
    delay(3000);
    Serial.println("__TENSORFLOW MNISTModel");
    
    // configure input/output
    // (not mandatory if you generated the .h model
    // using the everywhereml Python package)
    //tf.setNumInputs(784);
    //tf.setNumOutputs(10);
    // add required ops
    // (not mandatory if you generated the .h model
    // using the everywhereml Python package)
    //tf.resolver.AddFullyConnected();
    //tf.resolver.AddSoftmax();
 
    while (!tf.begin(MNISTModel).isOk())
        Serial.println(tf.exception.toString());
}


void loop() {
 
    // classify sample from 
    if (!tf.predict(image).isOk()) {
        Serial.println(tf.exception.toString());
        return;  
    }
    Serial.print("Predicted class ");
    Serial.print(tf.classification);
    Serial.println("");
    Serial.print("It takes ");
    Serial.print(tf.benchmark.microseconds());
    Serial.println("us for a single prediction");
    Serial.println("");
    delay(1000);
}