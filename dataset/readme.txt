Implementation of Apriori

實驗比較圖：
  1.測試 1k 10k 100k在不同support threshold 下的runtime，x軸為support 1~6（次），y軸為執行時間
  2.測試 D1 與 D2 在不同的support threshold 下的runtime，x軸為support 1~6(%)，y軸為執行時間
  3.測試 D1 與 D2 在不同的support threshold 下的runtime，x軸為support 1~6(%)，y軸為執行時間/找到的itemset數目

Implementation of FP-Tree

實驗比較圖：
  1.測試 1k 10k 100k在不同support threshold 下的runtime，x軸為support 1~6（次），y軸為執行時間
  2.測試 D1 與 D2 在不同的support threshold 下的runtime，x軸為support 1~6(%)，y軸為執行時間
  3.測試 D1 與 D2 在不同的support threshold 下的runtime，x軸為support 1~6(%)，y軸為執行時間/找到的itemset數目
  4.比較 FP-growth 與 Apriori 在不同number of transactions 下的runtime，x軸為number of transactions 1k 10k 100k 1000k，y軸為執行時間
  
  
  ps：檔名對照
    1k    :T15I6N0.5KD1K.txt
    10k   :T15I6N0.5KD10K.txt
    100k  :T15I6N0.5KD100K.txt
    1000k :T15I6N0.5KD1000K.txt
    
    D1    :T25I10N1KD10K.txt
    D2    :T25I20N10KD100K.txt
    
    檔名參數說明
        T：平均交易長度
        I：frequent itemset平均最大長度
        N：商品種類數(每單位：1000種商品)
        D：資料庫筆數(每單位：1000筆交易)
        
    附上測試用資料檔
        Debug用data_T10I6N0.05KD0.1K.txt