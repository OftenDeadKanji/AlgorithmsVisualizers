package MVC.Sorter

class InsertionSorter : Sorter() {
    private var isInserting = false
    private var sizeOfAlreadySorterArray = 1

    override fun sortAndReturnIndex(arrayToSort: Array<Int>, currentIndex: Int): Int {
        if(isInserting) {
            return if(currentIndex > 0 && arrayToSort[currentIndex] < arrayToSort[currentIndex - 1]) {
                swap(arrayToSort, currentIndex, currentIndex - 1)

                currentIndex - 1
            } else {
                isInserting = false
                sizeOfAlreadySorterArray++

                currentIndex
            }
        } else if (currentIndex < sizeOfAlreadySorterArray) {
            val index = sizeOfAlreadySorterArray
            isInserting = true

            return index
        }

        return -1
    }
}