---
layout: post
title: First Results
---

A lot of time has passed since I last touched base on this project but I'm happy
to say that it has been all worthwhile; getting some first results have been
very encouraging. However, there is still a long way to go to generate
convincing tonal music.

#### Introduction
This project started out with the intent of self-teaching as well as I could the
subject of deep learning. In trying to build different models/implement
different heuristics, I learned quite a bit about each one's potential pros and
cons. For example:

* The [RNN](http://www.wildml.com/2015/09/recurrent-neural-networks-tutorial-part-1-introduction-to-rnns/) - By far the simplest and most mathematically 'pure' of the models
 used/attempted.
* The [LSTM](http://karpathy.github.io/2015/05/21/rnn-effectiveness/) - Only a
slight deviation from the ideology of the RNN, where the pitfalls of the
vanishing/exploding gradient problem are avoided by 'gating' computations
* NLP techniques to process and represent musical 'words'
[word2vec](https://www.tensorflow.org/tutorials/word2vec) and
[GloVe](https://nlp.stanford.edu/pubs/glove.pdf). Both were slightly too complex
for the young age of the project, but they both are very intriguing and I
intended to revisit.
* Other, more cutting edge models techniques such as GRUs, evolution-based
models, RBMs, etc.


Ultimately, most work has been done in Python/Numpy and has been
built/implemented using the Keras Library. You can find my code for training
a character-based LSTM [here](https://github.com/machine-music/char-rnn).


### Specifications
#### Data
A dataset was built using a self-made tool called ['midi-reduced'](https://github.com/machine-music/midi-reduced)
which transforms midi files into a reduced musical format that retains pitches,
the time they occur, and their duration (both in 100ths of a second). The notes
take the format: `<time since last note on><note number><duration>,`
These values are then stored in unicode and are delimited by commas. For
example, a rolled C-major triad with each pitch lasting 1 second would look as
follows:
```
In: notelist_to_notestring([[0,60,100],[100,64,100],[200,67,100]])
Out: '\xa0ÜĄ,ĄàĄ,ŨãĄ'
```

As for the data itself, midi files of Bach chorales were collected from the
[Humdrum Database](http://kern.ccarh.org/browse?l=371chorales). The collected
files were then run through midi-to-reduced, and concatenated to create a
complete and slightly small training file (680 KB).

#### Models
A total of 5 LSTM models were trained on the same dataset with varying
size/regularization hyper parameters.

| Model | Dropout | # Layers | Layer Size |
|:-----:|:-------:|:--------:|:----------:|
| Model1|        0|         2|         256|
| Model2|       .2|         2|         256|
| Model3|       .2|         2|         128|
| Model4|       .2|         3|         128|
| Model5|       .2|         3|         256|

These models were trained using sherjilozair's library [char-rnn-tensorflow](https://github.com/sherjilozair/char-rnn-tensorflow)
as it ran much faster than my own implemented version. Code was run on
an AWS EC2 p.8xlarge GPU machine running Ubuntu.

### Results

Below we find the output of the loss function of each model plotted over time.


Model 1: Finishing with Loss = .02 after only 150 Epochs
![Model 1 Loss]({{ site.baseurl }}/images/firstresults_Model1loss.png)


Model 2: Loss = .81 after 200 Epochs
![Model 2 Loss]({{ site.baseurl }}/images/firstresults_Model2loss.png)


Model 3: Loss = .98 after 200 Epochs
![Model 3 Loss]({{ site.baseurl }}/images/firstresults_Model3loss.png)


Model 4: Loss = 1.20 after 200 Epochs
![Model 4 Loss]({{ site.baseurl }}/images/firstresults_Model4loss.png)


Model 5: Loss = .86 after 200 Epochs
![Model 5 Loss]({{ site.baseurl }}/images/firstresults_Model5loss.png)


And finally, a set of short 'pieces' composed by each model:

Composition by model 1:
<audio controls>
  <source src="/audio/firstresults_composition1.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

Composition by model 2:
<audio controls>
  <source src="/audio/firstresults_composition2.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

Composition by model 3:
<audio controls>
  <source src="/audio/firstresults_composition3.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

Composition by model 4:
<audio controls>
  <source src="/audio/firstresults_composition4.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

Composition by model 5:
<audio controls>
  <source src="/audio/firstresults_composition5.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

### Interpretation

In all 5 models and their compositions, it is clear that an adequate
understanding of rhythm has been accrued. The less under-fitted models, however,
seem to have serious trouble grasping the ideas of tonal harmony, leading to
very dissonant chords being pretty common place.

Obviously the lack of dropout in Model 1 has a huge effect on the acquired loss.
This lack of regularization has created the most over-fitting of the five
models, which is evident in it's "composition" - a note for note plagiarism of
Bach's works. The mission is instead to create new 'original' music, so rote
memorization is largely a failure.

It is also apparent that the bigger models consistently under-perform the
smaller ones, leading to model 2 producing the most apt results. This is likely
due to the small size of the data set - something that can be adjusted moving
forward.


### Future plans:
While the current results are exciting, there are still quite a few streams of
improvement. Pushing forward with the LSTM architecture of model 2, these are:

* Messing with different values of Dropout
* Getting a larger Bach data set, possibly his collection of keyboard music
* Different Composers
* Creating a dataset where all pieces are normalized to C-major

Expect updates in the next few weeks!
