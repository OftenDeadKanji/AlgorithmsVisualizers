package MVC.Sorter

class BubbleSorter : Sorter() {
    override fun sortAndReturnIndex(arrayToSort: Array<Int>, currentIndex: Int) : Int {
        return if (currentIndex < arrayToSort.size - 1) {
            if (arrayToSort[currentIndex] > arrayToSort[currentIndex + 1]) {
                swap(arrayToSort, currentIndex, currentIndex + 1)
            }
            currentIndex + 1
        } else {
            0
        }
    }
}