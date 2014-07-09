package org.tp;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class FileWrapper {

    static private final Map<String, ReentrantReadWriteLock> locks = new HashMap<>();

    private ReentrantReadWriteLock lock(String fileName) {
        synchronized (locks) {
            if (locks.containsKey(fileName)) {
                return locks.get(fileName);
            }
            ReentrantReadWriteLock value = new ReentrantReadWriteLock();
            locks.put(fileName, value);
            return value;
        }
    }

    private void unlock(String fileName) {
        synchronized (locks) {
            locks.remove(fileName);
        }
    }

    public String read(String fileName) throws IOException {
        ReentrantReadWriteLock lock = lock(fileName);
        lock.readLock().lock();
        try (FileInputStream is = new FileInputStream(fileName)) {
            byte[] content = new byte[is.available()];
            is.read(content);
            return new String(content);
        } finally {
            lock.readLock().unlock();
            unlock(fileName);
        }
    }

    public void write(String fileName, String content) throws IOException {
        ReentrantReadWriteLock lock = lock(fileName);
        lock.writeLock().lock();
        try (FileOutputStream os = new FileOutputStream(fileName)) {
            os.write(content.getBytes());
            os.flush();
        } finally {
            lock.writeLock().unlock();
            unlock(fileName);
        }
    }

}
