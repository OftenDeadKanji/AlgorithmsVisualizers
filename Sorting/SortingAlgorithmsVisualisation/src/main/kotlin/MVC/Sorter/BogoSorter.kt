package MVC.Sorter

class BogoSorter : Sorter() {
    override fun sortAndReturnIndex(arrayToSort: Array<Int>, currentIndex: Int): Int {
        arrayToSort.shuffle()

        return -1
    }
}