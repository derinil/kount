kount is SIMD accelerated line counter. it can count other bytes too. only ARM Neon is supported.

Benchmark against wc and [ct](https://github.com/parof/ct) (compiled with -Doptimize=ReleaseFast):
```
hyperfine --warmup 5 'wc -l 1Gb.txt' './ct 1Gb.txt' './bin/kount 1Gb.txt'
Benchmark 1: wc -l 1Gb.txt
  Time (mean ± σ):     415.4 ms ±   2.6 ms    [User: 342.9 ms, System: 72.1 ms]
  Range (min … max):   410.5 ms … 417.8 ms    10 runs
 
Benchmark 2: ./ct 1Gb.txt
  Time (mean ± σ):     242.6 ms ±   0.7 ms    [User: 169.9 ms, System: 72.3 ms]
  Range (min … max):   242.0 ms … 244.7 ms    12 runs
 
Benchmark 3: ./bin/kount 1Gb.txt
  Time (mean ± σ):     117.5 ms ±   4.7 ms    [User: 53.6 ms, System: 63.6 ms]
  Range (min … max):   115.8 ms … 139.4 ms    25 runs
 
Summary
  './bin/kount 1Gb.txt' ran
    2.06 ± 0.08 times faster than './ct 1Gb.txt'
    3.53 ± 0.14 times faster than 'wc -l 1Gb.txt'
```
