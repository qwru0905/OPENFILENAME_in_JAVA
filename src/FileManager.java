public class FileManager {
    static {
        try {
            System.loadLibrary("filemanager");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("네이티브 라이브러리 로드 실패: " + e.getMessage());
            e.printStackTrace();
        }
    }

    public native String selectFile();
    public native boolean saveFile(String content, String fileName);

    public static void main(String[] args) {
        FileManager fm = new FileManager();
        String selectedFile = fm.selectFile();
        System.out.println("Selected file: " + selectedFile);

        boolean saved = fm.saveFile("Hello, World!", "test.txt");
        System.out.println("File save " + (saved ? "successful" : "failed"));
    }
}