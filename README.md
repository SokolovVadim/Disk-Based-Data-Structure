# Disk-Based-Data-Structure

### Build

```
cmake -H. -Bbuild
cmake --build build
```

### Usage

```
cnt::Container<uint32_t> c(65535);
for(uint32_t i = 0; i < 65535; ++i)
{
    c.addElem(i, i);
}
c.getElem(0);
c.getElem(128);
c.getElem(1025); 
```
