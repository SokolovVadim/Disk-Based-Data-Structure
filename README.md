# Disk-Based-Data-Structure

### Build

```
cmake -H. -Bbuild
cmake --build build
```

### Usage

```
    cnt::Container<uint32_t> c(10);
    for(uint32_t i = 0; i < 25; ++i)
    {
        c.addElem(i, i);
    }
    c.getElem(0, 0);
```