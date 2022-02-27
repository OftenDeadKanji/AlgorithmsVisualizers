package MVC.Sorter

enum class SortingAlgorithmType {
    NONE, BUBBLE, INSERTION, BOGO, QUICK;

    companion object {
        fun StringToEnum(value : String) : SortingAlgorithmType
        {
            return when (value.toUpperCase()){
                "BUBBLE" -> BUBBLE
                "INSERTION" -> INSERTION
                "BOGO" -> BOGO
                "QUICK" -> QUICK
                else ->  NONE
            }
        }
    }
}