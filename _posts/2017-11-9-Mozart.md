---
layout: post
title: Machine Musicianship: Mozart
---

New results are in for this week's set of trials. I will try and keep this
update brief but meaty. For an intro, refer back to [First Results]({{ site.baseurl }}/2017/10/26/First-Results.html),
as this post will just be an update.

Following my last post, I had set forth 4 new directions to move this project
towards, listed here:

* Messing with different values of Dropout
* Getting a larger Bach data set, possibly his collection of keyboard music
* Different Composers
* Creating a dataset where all pieces are normalized to C-major

This past week, I have been able to fulfill a couple of these objectives with
promising results. My 5 most recent models have been LSTMs with the same network
architecture as decided on last post (2 layers of size 256) with varying degrees
of dropout. This week's composer was .... Mozart! Specifically, the collection
of Mozart's Piano Sonatas.

### Specifications
#### Data
Once again, this new dataset was built using a self-made tool called ['midi-reduced'](https://github.com/machine-music/midi-reduced)
which transforms midi files into a reduced musical format that retains pitches,
the time they occur, and their duration (both in 100ths of a second). More info
at [First Results]({{ site.baseurl }}2017/10/26/First-Results.html).

Data on Mozart's Piano Sonatas was provided by S.D. Rodrian on his [Mozart
web page](http://mozart.sdrodrian.com/). The resulting 'Mozart_PS_reduced.txt'
was 1.7MB, a decent upgrade from the puny Bach Chorale dataset.

#### Models
A total of 5 LSTM models were trained on the same dataset with fixed size and
varying dropout hyper-parameters.

| Model | Dropout | # Layers | Layer Size |
|:-----:|:-------:|:--------:|:----------:|
| Model1|      .05|         2|         256|
| Model2|      .10|         2|         256|
| Model3|      .15|         2|         256|
| Model4|      .20|         2|         256|
| Model5|      .25|         2|         256|

These models were trained using sherjilozair's library [char-rnn-tensorflow](https://github.com/sherjilozair/char-rnn-tensorflow)
as it ran much faster than my own implemented version. Code was run on
an AWS EC2 p.8xlarge GPU machine running Ubuntu.

### Results

Below we find the output of the loss function of each model plotted over time.
Each Model has been trained for a total of 400 epochs.


Model 1: Finishing with Loss of 1.10

![Model 1 Loss]({{ site.baseurl }}/images/mozart_ModelLoss1.png)


Model 2: Finishing with Loss of 1.15

![Model 2 Loss]({{ site.baseurl }}/images/mozart_ModelLoss2.png)


Model 3: Finishing with Loss of 1.25

![Model 3 Loss]({{ site.baseurl }}/images/mozart_ModelLoss3.png)


Model 4: Finishing with Loss of 1.25

![Model 4 Loss]({{ site.baseurl }}/images/mozart_ModelLoss4.png)


Model 5:  Finishing with Loss of 1.35

![Model 5 Loss]({{ site.baseurl }}/images/mozart_ModelLoss5.png)


And of course, a set of short 'pieces' composed by each model:

Composition by model 1:
<audio controls>
  <source src="/audio/mozart_composition1.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

Composition by model 2:
<audio controls>
  <source src="/audio/mozart_composition2.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

Composition by model 3:
<audio controls>
  <source src="/audio/mozart_composition3.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

Composition by model 4:
<audio controls>
  <source src="/audio/mozart_composition4.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

Composition by model 5:
<audio controls>
  <source src="/audio/mozart_composition5.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

### Interpretation

This set of models has proven both very interesting and exciting with the set of
results. The larger dataset has made a significant difference on the models'
performance in learning. Model1, in particular, with its small dropout, has
managed to gather a firm grasp of harmony in addition to rhythm, with a strong
sense of key-center throughout the duration of its composition.

I was so happy with this model that I decided to let it compose a longer, 9
minute piece to let it really show us what it's got. What I love about this
model is its tendency to go on 'rhythmic tangents' - where suddenly, the
network, having seen pitches in rapid succession, will start composing extremely
fast virtuosic lines as it has learned from the piano sonatas it has trained on.
Listen for this in this longer recording at :30 and 1:02.

<audio controls>
  <source src="/audio/mozart_composition1extra.wav" type="audio/wav">
  Your browser does not support the audio tag.
</audio>

As for the other models, their performance seems to have decreased monotonically
with the increase of dropout value. Moving forward, I think that the most
satisfactory results can be acquired with larger datasets with a lean network
with a small (.05) dropout rate - which has been proven to be useful from these
trials (acknowledging, however, that dropout and model architecture are not
necessarily linearly independent parameters.).



### Future plans:
I am very happy with this week's results - and even more about what I can
accomplish moving forward. After a bit of digging, I have found a tool that will
facilitate a heuristic that I have been thinking about for a while: normalizing
inputs to a key center. To do this, I will likely be using a neat tool created
by researchers at CMU called [Melisma](http://www.link.cs.cmu.edu/music-analysis/)
which implements a novel algorithm for key-finding of midi.

So, over the horizon:
* New, larger datasets. I am looking into doing Chopin piano music, or possibly
collection of composers
* Key normalization with Melisma

Distant future:
* Testing a Convolutional-RNN: A very promising and extraordinarily powerful
model.


Expect an update in about one month!
