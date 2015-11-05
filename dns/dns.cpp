#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using s=std::string;using t16=std::int16_t;s b64c="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";bool is_base64(unsigned char c){return(isalnum(c)||(c=='+')||(c=='/'));}s input="QQAMAO0AUgBHAH0ADABtAF0ALQAtAAwATQDtAE0AGQCCAIsAbQB9AIIATwD9AE0ADABsAAwAggDbAO0A2QB9APkAiQCdABQBLQAOAU0A8ADwAAcBCQELAQ0BDwERARMBFQFNAPgAJwFBAPkADABdAG0ALQADAQsBBgEIAS0AvQBNAIkA3QBNAC0ArQDtACwAOwGJAPkAXQCdAHkAjQCJAEUBGQAMAEkBggB/AC0AXQAaAX8AiQALATUBCAGCACsALQCJADoBPQAQAQ0BLQD9ANkARQFDAQwAvQAbAfkAGwEZAFEBCAE9AAgBeQBdAPkAvQBdAB0AOgESAckAfQBMAV0AWgFJAV0AyQDZAOwADABBACQBvQD9ABQBUQEXAdkAIwEZAK0AbgGLADwB7QDtAHkAfQCJAFQBnQDNAF0A7QAMAFYByQBNAGwBiwAdAK0AcAEMACABggBvAMkAUwHbANkAXQBRAVQBWgEXAWwB2wAZAAMBrgGwAY0ByQAUAZcBFwE9AA4BFAHJAJIB+QAXAQcBnQCGAYUAggD7AC0AeQAXAUgAWAAIAGwAiAAIAAgADACdAKIBbQBtAEcBdgFSAfkArQAJABkAwgFPALQBJAGoAQ8B2wDNAM0ArgG9AdsAmgF/AMkAVwHtABsBsAF4AR0AcwEZAIYBggBzAFYBcAEMAQUB/QAIAZ4B8AGdAEcBPQCtAEwBOwEpAVYBvQAMAH0BGQBsAU8AnwFLAXkA3QCtAMkAbQAUAb0ARwEaAvEBsQFeAQ4CCAEPAfEBUgE2ATUBTQBcAS0AJAK9AVkBDAAZAIMBcwGJAAUCDABZAA8BEwIMABcCvQCSARAB+AEOAYYBNAE2ATgBAwFRAY8BfwA7ApcBDADNAAMByQBKAhgCqwEZABYBHQJ0ATsBzQB9AG0AzQAQAVkAHQDZAE0ATQIwAr0BXwEgAn8AnwFsAV8BGwHtAFkC2wD5ADoBOgLNAAwBDAAJAH4BBwHtADcCKwJHAX0AqAFCAZ0ATAHMARkBswEMALAB8gH9ACQCvQB8AX4BdQF4ARkARwEQAhICnwFJAUwCDwErAJACRwCKAgwAmQEvAl4C4wEtAG0AKQLsACcB8AAAAVYCWAJaAlwCXgJrAW0BXQAJAFQBSwJHAAoBNwEIAfcBfQAiAjkBRwALAj0BowJZAosAUwLOAe0AXQAOAjACMAKLAWQCcQJQAYIByQBSAEsAAQF5AKsBLQAUATMCagGXAc0CDQEOAikCQgK1AocCCgK9AH0AsAFKAbgBRwBOAfUBXQB9AEcBFwHCAk4BDgEYAvQBTwC9AEACPAEJAbkCEAFvAp8BmwIjAcEBLQFSAVcCFwEfAW0ArQAOAn0A7QCdAIMBzgJZAfIBGgHvAYIBYwH7AJMBHQDUAlgBtAFKAlcCugJRAdsCsAItALMChgFxAM4BngGXAgEDgwGgAV0A+QE7AU4BXQAkA20AOgFJAeEB4wE3AokATQDlAgwAPQB9AB0ASwEvA4IBOQBZACMBmAIfAZ0AQwGtAG0AnwKhAu8CCgHdAF0BfwCrAm8AJALwAZ0BnwFjAU8AxAFtADkCOgFDATsCLQEtAkkBDACLAU8AGQBJAbMCDAAdAGgC3wLfAYMBqgKxATIB8AAZAWEAfQB9AUwBugGxAeUCEgEMANEBbADIANcBiQBZADwDogEtAxQCLQBzARsDdwF5AToBVgFLA3kArQIKASMBLQCGAWEAVAHyATACAQE3AS8CMQKAARoBTwAJAU0ACQCnAfMCjgNQAw0BTAGtAOsBHQIAA40BEQOkAosAWwJdAskARwEpA+IB5AFaATIDXQDDAp8BKQJFAZkDAgJWAXUCuQEcA8gBnAN5AJ4DzQCtAB0AGANnAwwAsQBvAbkBbgGvAbEBBQGHAz4DvgF5ALwCeQBbAdcCOgE3Ap0CUwFaAwsBHQBSAjkCGAIaAhUBjAERA/kAkQGaAUgDFgGfAhkB9QDjA60BxwO7AW8DVALHAWoDiAK/Ag8DOwG2Ad8CbQMZAMoDlANEAd0DSQK2AccDcAEFAWACXgH+AbEBLwIbASsCBQHbAuUCNQFUAf4BOwJNAggBTAIhA0MBTQAdADcCXQIKAXQClwGZAZsBVwHvA2sDiQIPAq0AjwHlAcMBFwH0AcgDvQBcA+0C8ABRADADwwE+AwsBPgGnARABAwJQA14CzQMXAUkBTQDNABYBPAGdALcCCQHyAx4CjANUAYsCMgSjAVkDRwREA4IBMwKbAUYERwEbATMCSgFOBH8AIgF/AEsDNgF9AmQCAQI9ATcBbAIEAfoBoQJcAUMCRwC+Ag4CLQNKBJcC4AFtAMYB4wEBAQADTgFHAU4BWQCrAjgCFwGtAl8CmgI+BIACtQHFA0cA9wP5AwkBzAMTAtAD7gGdAG4BSAMFAccBPQE/AUEBPQPtAIYBYwTSA5UCgQKLA38CLgIbBMQBeAEJAYwBzwIuA4ECFAQSAXUCSgLjAjMDiASzAVcBfgEcAzwD+QAdAE0AyQEMAEEDmgT+AggB3QJjAloBuwNWA+EDOwFjAYsAZQH9AAUBtAS9AE4BzAOLAA4CRAMEAwYE2wDJACQC7QDBA0EDDAJYAf4B4wENAWYDQQI3AdgC8AN/AQ4CJwNLALYBXwNZAR4EUgGDAV8DXwEDAQ8ELQEKAY4BkAE8AuUBawFPAk8AfgEwA9wDRQE5A1oBnQEXAs4BzwJIBKgBhwOGAdEACAECAUcAqAEDBbEDZAS1ApMDgwT8A88BvQRNAB4BDACNALMCLQBZAIEB8QSfAfoEzwGdAuIDcAIkBCsCkgFdA8AB9QTtAPcCzwIOA8gByQQRBEcAngGGAVEAbgHxAVEBFwJ1Aq0AWgGrAlUBXwNPAFkALQAHAgkC0APWAtkEOgFoAh4BIAEiAZQD5AFRAaMEwANABBcBEgW9ABQFtAHgAe0ANAWXAnoBRwCXA3UCWQOZA0YCAgP5AG4BKwDtAocB9AQZAlABgwEpAbMBogP+A1cF+ANUBUsB8gHtAB0AxwJZBMABfQCXA5sCTQBtABUFDAQuAtYCsATPASQBcgIGAdsE0AM7BFkClAO8A10FTQBAAggFQQX6A4QE0gJOAxcBFwFWAZ0AMgUcBesBpQQZBc8CogMJALEBXQDdALMBSgG9AFkEYAIpAQMBVQViBf0CUgUOAkwBowEYAq0AZgEbAvgA0QNSBOEDxAFXBJ8BPACSApQCCAJjBe0AfADzAxcBCQC2BYAB4QODAUUBDAA8AJoBTgM8AzACiQAZALwFqQV8AJ8CQQK0BRkAtgVUAWcE5ATJAHgBdQIhBYEFIARNA1ADRAP9ALUC4QTwAUcEeAQSAxABAQHiAvcBswFQBHECcwKeATcCEgUQAVkDDgM6AjwCpQHPAowBhgExAKwDWQC9AKIBQQQZBEsBuwO9A78DswJHAUwEVATwAUcB6QEaArcBJAKWBJQDGANhBU0FTwUGAc8CCQbIBEUDWQRPAQ4CBgUNBHECDAFAAeABPwFRAf4CkgH3AtEDQAW2AosDLwXcBXkABQJdAEcBHQBZAIgFOAUtA28DiwQMBO8BtQUJAtgFDAAqBuEDFwEZBRUEVAG9AGwAHgFTBCUBzQT8BLYBuwF4AfkAHgKXAV0AkgQAAcIFCQLEBWACxwXhAtsAvQDcBWsF1gLVBdcFZAIlBeUBRwQqBYkASwFQAosEkAP9AOgCkQHJAOsCHQbkBaYF7wV/AGoGlwFjAYoEtwLtAM4FyQA4A08A9QWLABgEBwNTBJ4FXgF8Am0CrwXPAeEESgZMBjsE4wFPBmkG0wWoAnoGqAVQAasBCQAVBVoEeQDdA84FDwKgBVkEFQNXBFMBSAOwAYwCpAasBIwBrwVdAt8BPAQjAYcFxgEEBgYByQLgBHkGYgRBAn0FFASABdkChAMcA6QFKgXAA9UCcQLEASQBjQD4A58BvgLZAMkCmgaRBGEFYAIyAjQCFAT+BHsF3wEqA6wDDwShBJ8BtQPzBbkBHQQvA8ICtgQjASYGLAOLAzEFAwK1AokAQAMAAdIEfQSVAYEGgwaFBloBGAYVBdcEAQHoBAEBfQWjBlkBSgHfAaED8wGWA6IBbAH/BsIGWwI+BFEGsQHPBBEFEwUVBb4BowEKBX8FNATXAwwC4wLZBR4FkQFuAeUBTQB9ALoCiAPRBJ4BVAQoAucBsgGZBFQBTQNJAg0BCQAJAGoBNgIRB/QDRgRRA7YC0AVFAUIBhAIXATwAZAY/BtYFQQZkAvID8QZaBgIDSQFdBr4FSATFBEkCXAN1AhwDhwPUAngCGwPtANwGjARCBA4CNwY5Bp8EPwSQAksAzwQcAgsCggXyA5IGxgHjBeUFZwQtBSgCNQEyAwMBagU7AZMFUwNDAdUDPATNAAQGQQccAUMFIQHmBjcCogGgA7ABCgF9AFEHUweLBZUEiwGLAIYDWgPjAXICdQIlBYsAowHuAvcGWgFIAAgAhgEsBwoHGwFhAusEPgZFB2YGTAcZAkUDWgH5BQwDCgZIAa8DMAJoBMYBlwPEAToGDgMAAzcGLQBPBz8EUwZVBcUGdAdWBzgGxgE6BokFcABBA7oFYATyAZwF5gU1AjcCuAXIADgA/AaXA/YGDwdaAYABYwKxA3EDGACTB5YDvwV+BJkGNgftADgHbwQVAl4BcAGSA2gGygUDBh8E8QMdBmABpweuBQ0DowFTAp0ABwbrAb8D1AIZA4AHGAI5AsQFAwS2BpMF/QC9AwwB3QFhBvAHkgVtBvEBMQaeAXUB6wFAAhoEmAGjBZEDVQRABL4CUAOLARIGoAFGBAYDTAXJB1IBFwVTAoAG1gX0BhMBlAELBxECdgGiB/EGtgHJABcCyQBFBVoBsQemBV0DKgUtAMgCrgKfArIEIgdVB98BVAEJADQGZgNpA6QE2QRQArEBkgJeB1QHPgFAAUIBRAEHBZQElgJ0BHYEzQd5BJkCzQTaA8sDDAUBBg4BDwJ3A3AHDgEkAWUCfwSBBCIEzgX+AjEIrwFdA4wBzwPyA2QGVQEFBE8BvQE4AtsCNwKdADoFrwfIAWMDSQH3AWYHYQUXByICHAcrAmoBGQEXAdkBDwV5AhQBhQaBBQ4BUQEZAcEB5AV3BTQFEgc6BAMEGwPmBfIBZwcUA9wCVAEzAw0HRQi+AUIDlAYtAYcGVgH5Ac8DGQeZAZ4H4wRsBskA5gS1AtwGWwVGBAMB6wT3BUQBcAHuAgwClQgQAbIB+wDaAj0BPwQeBecGAAI8BQoCbwecAikCOwLZA0kGtAf8BmwDFAFFBQgC+QBHAQYHVgacApIDGQGYCLEBpghLATkCVAFQAwcB8gGPAUgDOgH0AVUBZgIXA/MDCgjZBsQBWgGTBXUBRgFeA+MEcggFBIQHCgGVCC0DhgHEA2cCHAFSBBwDlQVTBT0IrQiUAUwGnQhSAagHkQHOAu8E/gNLAw8GBwgFAqkD4AGrAywDFQjzBnwIGQjzAxcCfQLHBMwB3wcmB5IELwgNAgUERAOnBUgIggY8A7oITgRPADwDWgSgBTQGWgENBLEBGgKlAa8E6QgjBBQBlwXIAUwCHwH5AQMBiQOsB54BPAY7AQMFBQFTAUYDNAZxAVsEzQDHCFEBmAISAt8IUAIWAbIFwAF0ATACtgMGBE8ACQD8CDMEHAeJAC8DpgEqB3kATwkdAukGSQZICRwDEgJGApgE5gE7AggCLQAMCc8BRQfPAi8DIgi9AZQBnwUrAKAI6ATjBswBLQBPCW8CgQJ5AlEBLAfuBFAJ2Qb8CH0BWQA3BEoCTAJQCBoJ1QPKBUUFUQFfBmEG8wXkAhoBbwC4CIIH3QRLAW0IfwPmBTMHRAb3AuUDkwTMAdYDeAkSAX0H8QfkBVwGbwZNAxkAXQkEBvwC/gIOAUcBhAeFAkUB0APdB8wBvwgiCN0DWQOiAZ8C0QA9BRABbAH7AAMGrgOwAzsBqgGsAVcITAjNA5ADzgXHAo0DeAGwAWwGlwVWAUkBUQQuAt4BaQRSBVAFlASjBUMB9gLCAZQBvgnqA+IC1gWqBCIJ8QFGAlYG7QYMAOEAfQW9AxoG3wnPBmIJ/ATLB84EFAbJAIsHtwg+BYIHEweOBQ0FhgncBQ0HDAnzA60IHQeXAloBTwMXA2AF7QjOAu8I7wHxCFABUwV/B+IIUweUCJoC6wX3CAQDbAZCAzoISAH6CK8F/AR9BAwE+wCZCRIJggBDAM0EbACeCAQJKwP8BD0IvwJnBKgAMwGQA+8JgAE0AvEGqgMkCu8EZAiTCD8FZQTdBIsDnQUPAp4BHQBsAW8AjwFfAT8EKAT2ASsELwPABsEJhQQ2ASsISAkCAoEB5AepByYFEgesBzoFqwiyCEIKvwJ5AboGVQJ/CSAGKQNNAt0IGQAJB34EyAMZAM8ECwZdAWIC7QnhAm8AOwIOApwEsQFTBnAIAAEwCqwDmAWvA3YBqQTBBzQK3wWIAkcK/QNdAMgJXQDKCcQFBwJ0ATMH2Qn3A9sDnQAkAWYBFwEIAWcHYAgUBh8FTwlaCEsKywcUAlsEzwS/AokDjwm1Ai8FmgFfBR8GbQZIAyIDjASUBesGKAMjCnQK1gZRAYkAnAX1BRUGTQraBi0BiQBsAKwIDgr2CJwIEQo1BrYGeQTYBUEHSwkXCv0JJwT9BtYDWAJwAm4FMwM+AXcKBQNXAYcDEAFHAXkEDQl9AuUBbgR/B7AECwGoCKcBFAMtAgcBhwmIA7oHQQNzCiwDEwhlCGUCfQAUBL0AOgXrBewJkwWSA1wGRgSzAh4HLwRaA+UKvAPVAlEFmQPdCEQELwkrBfcKKwHPAeQGWgE3AkwJIwH8BGwG2wHcAggBmgNxAq4IrwWLBzADrAMUAcQIzwOzBfsA/QBTAe4IegKvA+UFeQZzASoCngECA/gBnQUZALYDCwT/Ck0AbAB/AZ0HbQqWA8UE5wFrAecKiQHqCiUETwCZA18DHAFhA98GtwOABJsByQJAA0EDDAl3BU8JhAnOApQB4wHNANQEGwIQCywDkQUTCgIGXQD5BjsCWAIAA5ABiQpCC88CRAvrBUcLSQvsAjUCrAUNAbwE0wdRAdUHgAizBT0HmwcnBxADQwdcBsYFpAQZAZUIUghdBUoLSwfBArMCngawCSoJ+AcLASkBIQQ1CrUCBgMjCf8BDQcgCAMEVQYhBP4DbwE/CVoB3QdRAawFDwSvBe0H4wmPA8gBVgEJANMDIQNeCPQEuAiZAkgLOggmBlgKLgIzCncEggd9CtADVgJRBbwDWgEaB3cJ8go6CxwI+QD5AXAI0QSwBEABcgeIBkAGtwVwC5wCzAFHAV0CCgJlBj8HdQJvCZoBzQGpC5wLXAsOAq0JkAUtBmUEBgTxAUELbwS6A+0FRAqZAokHLAMDBjAGSQaeAdICfwALBhQB/QAnCYIJFAGRCvcC7gI6CzQC3QDOCEsFxwueC4IBwAcIAWEBtgLYCFMJLwS/BJYDWQVwAiIIrQc2AbUCxgizAQMBlwWQAdUJNQtwAp0ChAkQAQUGnQBbB10H7AC6B1kGwwVFB20LmQOtBK8EPAOXBVsLOghKC14EUgd2AWIBrANFAgIMDgPbAtMFBAgfBxwDfgtrByUGKQPAArcKegPxB5YBTgfnBwsB+gdNAgcLawGyCFYBqQWvBA0H5gI8BFwLnwcJAlcL5QFZC+UBaAktAEwAwwOLAx0A+gZHANIKzALUCr8D5AQiAUgDBQLwBZsJCgsKCp4B3AZKDLAC5gFNAEkHzwEBDGcLwQu6CxoC+wDsC3ABJgSTA2kM8QHPBKsI8goPBMcCzwYYDGkM7ALtAxsDogUnDJkHuAvYBboLMQSjBFcC9wRWCU4DlwICA58BjQKTCEQGHAciAjcMQgQHASQLuQM9AUkGjAtHAXcDzwHUAtwGQQttBFgLjAFFC0sLzwIBBuADkQGABsIItQGOCJQDEAHuApoMQwudDFoLPgwZDF0L9QheCXELWQdGAlUFjAudCY0IzAsJBYQHUgrnAa4JyAGdATACIQupBAkLCgGCAVgCLAUMABoD4gg/BMIMjwnAB0YGHwfEARIFZAnvBC4GzwwKDJsByAXVA+ED4QGMAecKvwXxBt0A0wytABUEngE+A4kFDADIAGwAGABYAcgJaAzjAe4LZwWoAmMKAwEnDJ8M7wTdA00C2wJ4BSsDiwfuBpYEfwCnBd0HoQRFC6gGAgFLAJMFOwF0DDcCogVwAlYBzga2At4HzAWAAc8FIwUOAzwAawsRDMQBRwe2Aa4BJAXNCEcAygFNAP0A0QlHAd0IfgGyAysCGwLxCQwNrwx1DA4DKAy2At8ISwetB8IBZwzZDDQGagPdCQINBA2sA/wHlgFXBhoBcwDZAPgDSgEzA9sCQAT1CCgN/QbZDAQDWwMcB2YMcwlEBXkHWggwB3cEmAagCIACSQXdA/ME3QgIATcLwgsSBoYB8QADAu0AkwUBBFsChAR2A1IHYgN9AaQERgZBDJsMQwytDIsArApIDdcI6ATYCBkEAAOBDLAKcALqB3MHMw1lCG0KrQCNABICbgSgBKMEUQENDd8D3QjuCzoB6QTDAS0DswLrAogDYQWrDJwMWgOeDPMMWQG+CtUC6wFNAMEB0wotA3kKOAKRB+8M/QRIBUsBCwwoCCgCEQVsBgYHzgGoAu4IaQIFAoYB4QCPA5kB0whHBAgCCgIYBPICcALTB6gGGQCGC0MGOwKIBSEKuwxMAkoLjgsYAhwEHQkRB20KvA1XCUcCzwZWCu4Fnw16BgAF8QM5DJ0BjQwKAbABlgE9BooLLg09DJ0L/wGRDfIL+waOC6IBog3eBsMBDgMDBU4MzwLVCvwLtgNMAp4K8gFRBIsJ0APsCSECcgVeA7QLLAHxB2EJeQHLCvAB2QWAAQ0EdQEFAZgCgg2NByoK8AZ2Bx8BeAdGBeMBEw6yCEIFFg5FBb8M1wP+A7sBtgPzB4wEFgiCBgkJ6wVYDZ8BjQANBHIMygJbBXYBbgzLDO8HTQIzDQ4C6AhrDIgHoQOLBzIM3QjZC0cCAAiaCgwAtQkzBXgJvw2GBDsKxwKWCqADbwUcA74ELAeZA7ID0QlUBQAMHAMwDnILXwVmCx0BHQ5WDfoBYQV3Bx4OTwjIAaUHoQOzAYUD+wmWA2UO5QEgB5ADEg2zB1IEggGfAkgAigVDCD8EZA7CC+IEDA0hApYHSwMyAdUAbwoDAV0FIAPkCC0CSg1RBPoD/QChBL8LXwGJDoMBuQHQCGQCwQbNBzsIlgf8C1QBVAowCGMOvwJlDuIE3Aa+AgYOeQEdAOcNjQkTCDYMlQpsBpcKFgLcAxsCQANpAwYDnARDA94NzwQpChkBIQCMAUkByw2rC08JrA1CBDID5wlFBFgEMwlIBIoBeQvtALQODADVAAwBuQ7tBE8JzA1HAPECxwRFAS8D0A6mA14C8wLHDskO7QDLDv4HgAK+C9ADtAiQBncJBg13BXQBKAhlBNAOIAeoALIEGQHZDtQCyw0rDFMIcAJ5BOUGlAMbBxsGXgedAQoDDAP3DsYIfQAWA9oNsg3wACYKrgPGDsID2Q7LDaEOXw2PA6AFVgF3AjYBbAaQDEAEKgX/DoADLwbxAaIB/QDgAS8LJgrcBSkKQAuICVoN5gW/AhAIkQrnBnoOXwV8DsIGAwxEAUsMyAEyB2MKUwZ7AT0CRQEyAXMODAC2DosAPAOJAEsMVgGgASkCego/AckAFgEyA6cJkAPbAnUCOw8/BHQHrgNiBMgALQUpAUsMyQRrAV4CQw+vBKID4wV5AdAI2wAEA6AD/ggcAxUCXQOvBScJRgwLAs8CswIDBvoLOgXMCfUMyAlLDBwP8ATCC7kJ9wUSB7oOnwR5ArUNBAppAm0BqAobAQIDogWmCHYOmw51ArABWwGmCWIEiAAtBXwGQgbCBakELQBLDHAOAAc9CNAOKAZwBO0ATgHbDskAngq9C+YG4Q7NDp0BtQLOAl8FHg8uCNgEzQuMAToOwgsdB2YDNg8BBWYC2QOYBsgIBwGoDhALvwFwAWYKAgJuDyYHnwYMC04D6wIYBO4CYA7mBm8F6wViD5AEQgJhDTALPg+XA4gNFAFWD7sPkA8TBIQC2grLBO4BPgF7D0cAfQf9DdoCaAJWBusBKg/WC/cCUQzfAyYKHQCYDg0CVA0XDucBkQUqArYDxQ/bCAYHXQUKC+kBTwZkAgIC4whhCC0HHAPdCMEBSQGXDRQDdgFZDzACHQBuD50JWQ8DDEADTg8aAdcAiQYcB80ENQL9AFUPHwn/BjIEmgFpCWcK/gEzB/wP+QCXDQQQqA8sAxMLjgOxDYYINQFZABAQnQHcBLEB7gIeEJoF9AM6BU4BSQdpDIUHNwyuBKIOIAPJBFQBEAskAaYChgFVABAQHgdLDCAIhAsGCp8B/QLgAZ0AFgEOAxUCmAYJAEoB/gGfD4kJWwfaCCgDcgJlCAUGeA7jCHwL2QWIC0YDagXaA3cK9Q5qAT0M1gtmD7cGSwB9BwUEWwVdEE0LDALQDoYB1QB8Ck8AXQXdAX8BkAz0AoMBAwRjCFcBnQKiAdkDxwXbAjsBwQ8YDuQKvgFMACcBiA8MAP8FgQVvBQYHvA5WAY8PhwdpDjMF/wE1EPwPRQGeDEUQNw2RAWEGagEeEEkP4w/1C8AEowFFD8ABZAFDAf0AHgKJCGcFgA++DF0CRQpeBP8C9QrFDjkQFQRdApcGiABLEPUM4QMJBAMEaALsAdsMcgcdBXoLRw47AckEpgheAW4NEQ17AV4EogOhBl0DUwZUAZwJYAmJCkQJJwGyBEEAJQwCDoEQLwuiCxQCAxAKD1ADDA8jArENxgRHBBAGlge8EFkBjQ2RENUEIwHlAkEJBAb/CDMMwwG9BKUQsAVOA/4C8wJQB/4BhA+FBRkCWQypDqwC/At1D2kG8QczAxsQIwbJBAsGGAKtB4kO9A3MAjkPTwxXA1MGKgUYAmgBiQDECEwA";int main(){int il=input.size(),i=0,j=0,in_=0;unsigned char c4[4], c3[3]; s ret; while (il-- && (input[in_] != '=') && is_base64(input[in_])) { c4[i++] = input[in_]; in_++; if (i == 4) { for (i = 0; i < 4; i++)c4[i] = b64c.find(c4[i]); c3[0] = (c4[0] << 2) + ((c4[1] & 0x30) >> 4); c3[1] = ((c4[1] & 0xf) << 4) + ((c4[2] & 0x3c) >> 2); c3[2] = ((c4[2] & 0x3) << 6) + c4[3]; for (i = 0; (i < 3); i++)ret += c3[i]; i = 0; } }if (i) { for (j = i; j < 4; j++)c4[j] = 0; for (j = 0; j < 4; j++)c4[j] = b64c.find(c4[j]); c3[0] = (c4[0] << 2) + ((c4[1] & 0x30) >> 4); c3[1] = ((c4[1] & 0xf) << 4) + ((c4[2] & 0x3c) >> 2); c3[2] = ((c4[2] & 0x3) << 6) + c4[3]; for (j = 0; (j < i - 1); j++)ret += c3[j]; }std::map<t16, s> d; for (t16 i = 0; i < 256; ++i) { d[i] = s(1, i); }t16 ds = d.size(); std::vector<t16> da; da.resize(ret.size() / sizeof(t16)); std::memcpy(da.data(), ret.data(), ret.size()); auto b = da.begin(), end = da.end(); s w = d[*b++]; s re = w; s e; for (; b != end; b++) { t16 k = *b; if (d.count(k)) { e = d[k]; } else if (k == ds) { e = w + w[0]; }re += e; d[ds++] = w + e[0]; w = e; }s o; {std::map<char, char> d{ {0,'A'},{1,'C'},{2,'G'},{3,'T'} }; for (char c : re) { o.append(1, d[((c & 0b11000000) >> 6)]); o.append(1, d[((c & 0b00110000) >> 4)]); o.append(1, d[((c & 0b00001100) >> 2)]); o.append(1, d[((c & 0b00000011))]); }}std::cout << o.c_str();}
