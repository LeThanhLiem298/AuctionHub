# AuctionHub - Reflection

## 1. Algorithm Justification

### Task A - Insertion Sort

Most bids in the Live Auction Monitor arrive in nearly sorted order. Insertion Sort works well in this situation because only a few elements need to be shifted. Its best-case time complexity is O(n).

### Task B - Selection Sort

The Top-K Bid Finder needs to find the highest bids from a small dataset. Selection Sort can do this by finding the maximum value in each pass. It takes O(n²) time but only requires O(1) extra space.

### Task C - Interchange Sort

The Price Anomaly Validator only processes batches of up to 50 bids. With such a small dataset, the O(n²) time complexity of Interchange Sort is acceptable. The algorithm is also easy to implement and understand.

### Task D - Bubble Sort with Early Stop

Bubble Sort with Early Stop can check whether the bids are already sorted. If there are no swaps in the first pass, the function returns true and the program prints STABLE. In this case, the time complexity is O(n).

### Task E - Quick Sort

Quick Sort is a good choice for large historical bid datasets because its average time complexity is O(n log n). Using median-of-three helps reduce the chance of selecting a bad pivot.

## 2. Quick Sort Performance

| Property | Result |
|---|---|
| Dataset size | 100,000 bids |
| Pivot strategy | Median-of-three |
| Runtime | 127.551 ms |
| Sorting verification | YES |

I used `std::chrono` to measure the sorting time in milliseconds.

## 3. Bug and Debugging

During testing, I noticed that Bubble Sort kept running even when the array was already sorted. After checking the loops, I found that `swapped` was not reset to `false` before each pass. I moved its initialization inside the outer loop so that the algorithm could stop early when no more swaps were needed.

## 4. LLM Usage

**Prompt 1 (Green Zone - Understanding):**

Explain why Interchange Sort is suitable for small datasets despite its O(n²) time complexity.

**Prompt 2 (Yellow Zone - Pseudocode):**

Provide pseudocode for selecting a median-of-three pivot in Quick Sort.

**Prompt 3 (Green Zone - Testing):**

Suggest edge cases to test sorting algorithms when multiple bids have the same amount but different timestamps.

## 5. Worst-case Complexity of Median-of-Three Quick Sort

The worst-case time complexity is still O(n²).

Median-of-three chooses the median of three elements: the first, middle, and last. The selected pivot may still be far from the actual median of the array.

If Quick Sort keeps dividing the array into uneven partitions, its running time can reach O(n²). On average, its time complexity is O(n log n).