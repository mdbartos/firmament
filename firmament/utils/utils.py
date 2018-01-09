import re
import copy

def extract_values(d, term='value'):
    extracted = copy.deepcopy(d)
    walk_extract(extracted, term=term)
    return extracted

def walk_extract(node, term):
    for key, item in node.items():
        if isinstance(item, dict):
            if term in item:
                node.update({key : item[term]})
            else:    
                walk_extract(item, term)

def recursive_get(node, keylist):
    if keylist:
        key = keylist.pop(0)
        node = node[key]
        return recursive_get(node, keylist)
    else:
        return node

def recursive_pop(node, keylist):
    if len(keylist) > 1:
        key = keylist.pop(0)
        node = node[key]
        return recursive_pop(node, keylist)
    else:
        key = keylist.pop(0)
        return node.pop(key)

def recursive_update(node, updatenode, keylist):
    if keylist:
        key = keylist.pop(0)
        node = node[key]
        return recursive_update(node, updatenode, keylist)
    else:
        for subkey, subvalue in updatenode.items():
            node.update({subkey : subvalue})
        return None

def collapse_level(d, keylist):
    _keylist = keylist.copy()
    values = recursive_pop(d, _keylist)
    _keylist = keylist.copy()
    recursive_update(d, values, _keylist[:-1])

def camel_to_under(s):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', s)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()

