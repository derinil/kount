kount is SIMD accelerated line counter. it can count other bytes too. only ARM Neon is supported.

Benchmark against wc and [ct](https://github.com/parof/ct) (compiled with -Doptimize=ReleaseFast):
```
hyperfine --warmup 5 './ct 1Gb.txt' './bin/kount 1Gb.txt' 'wc 1Gb.txt'
Benchmark 1: ./ct2 1Gb.txt
  Time (mean ± σ):     244.0 ms ±   0.9 ms    [User: 170.3 ms, System: 73.2 ms]
  Range (min … max):   243.2 ms … 246.2 ms    12 runs

Benchmark 2: ./bin/kount 1Gb.txt
  Time (mean ± σ):     119.4 ms ±   4.1 ms    [User: 54.4 ms, System: 64.5 ms]
  Range (min … max):   117.7 ms … 135.5 ms    24 runs
 
Benchmark 3: wc 1Gb.txt
  Time (mean ± σ):      1.542 s ±  0.002 s    [User: 1.465 s, System: 0.076 s]
  Range (min … max):    1.540 s …  1.545 s    10 runs

Summary
  './bin/kount 1Gb.txt' ran
    2.04 ± 0.07 times faster than './ct2 1Gb.txt'
   12.92 ± 0.44 times faster than 'wc 1Gb.txt'
```
