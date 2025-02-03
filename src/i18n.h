#include <unordered_map>
#include <string>

// Lookup table for lowercase to uppercase mapping
const std::unordered_map<char32_t, char32_t> UPPER_TABLE = {
    // Latin
    {L'à', L'À'}, {L'á', L'Á'}, {L'â', L'Â'}, {L'ã', L'Ã'}, {L'ä', L'Ä'}, {L'å', L'Å'},
    {L'æ', L'Æ'}, {L'ç', L'Ç'}, {L'è', L'È'}, {L'é', L'É'}, {L'ê', L'Ê'}, {L'ë', L'Ë'},
    {L'ì', L'Ì'}, {L'í', L'Í'}, {L'î', L'Î'}, {L'ï', L'Ï'}, {L'ð', L'Ð'}, {L'ñ', L'Ñ'},
    {L'ò', L'Ò'}, {L'ó', L'Ó'}, {L'ô', L'Ô'}, {L'õ', L'Õ'}, {L'ö', L'Ö'}, {L'ø', L'Ø'},
    {L'ù', L'Ù'}, {L'ú', L'Ú'}, {L'û', L'Û'}, {L'ü', L'Ü'}, {L'ý', L'Ý'}, {L'þ', L'Þ'},
    {L'ÿ', L'Ÿ'},

    // Cyrillic
    {L'а', L'А'}, {L'б', L'Б'}, {L'в', L'В'}, {L'г', L'Г'}, {L'д', L'Д'}, {L'е', L'Е'},
    {L'ё', L'Ё'}, {L'ж', L'Ж'}, {L'з', L'З'}, {L'и', L'И'}, {L'й', L'Й'}, {L'к', L'К'},
    {L'л', L'Л'}, {L'м', L'М'}, {L'н', L'Н'}, {L'о', L'О'}, {L'п', L'П'}, {L'р', L'Р'},
    {L'с', L'С'}, {L'т', L'Т'}, {L'у', L'У'}, {L'ф', L'Ф'}, {L'х', L'Х'}, {L'ц', L'Ц'},
    {L'ч', L'Ч'}, {L'ш', L'Ш'}, {L'щ', L'Щ'}, {L'ъ', L'Ъ'}, {L'ы', L'Ы'}, {L'ь', L'Ь'},
    {L'э', L'Э'}, {L'ю', L'Ю'}, {L'я', L'Я'},

    // Greek
    {L'α', L'Α'}, {L'β', L'Β'}, {L'γ', L'Γ'}, {L'δ', L'Δ'}, {L'ε', L'Ε'}, {L'ζ', L'Ζ'},
    {L'η', L'Η'}, {L'θ', L'Θ'}, {L'ι', L'Ι'}, {L'κ', L'Κ'}, {L'λ', L'Λ'}, {L'μ', L'Μ'},
    {L'ν', L'Ν'}, {L'ξ', L'Ξ'}, {L'ο', L'Ο'}, {L'π', L'Π'}, {L'ρ', L'Ρ'}, {L'σ', L'Σ'},
    {L'τ', L'Τ'}, {L'υ', L'Υ'}, {L'φ', L'Φ'}, {L'χ', L'Χ'}, {L'ψ', L'Ψ'}, {L'ω', L'Ω'},
    {L'ά', L'Ά'}, {L'έ', L'Έ'}, {L'ή', L'Ή'}, {L'ϊ', L'Ϊ'}, {L'ί', L'Ί'},  
    {L'ό', L'Ό'}, {L'ύ', L'Ύ'}, {L'ϋ', L'Ϋ'}, {L'ω', L'Ώ'},
};

// Lookup table for uppercase to lowercase mapping
const std::unordered_map<char32_t, char32_t> LOWER_TABLE = {
    // Invert the UPPER_TABLE
    {L'À', L'à'}, {L'Á', L'á'}, {L'Â', L'â'}, {L'Ã', L'ã'}, {L'Ä', L'ä'}, {L'Å', L'å'},
    {L'Æ', L'æ'}, {L'Ç', L'ç'}, {L'È', L'è'}, {L'É', L'é'}, {L'Ê', L'ê'}, {L'Ë', L'ë'},
    {L'Ì', L'ì'}, {L'Í', L'í'}, {L'Î', L'î'}, {L'Ï', L'ï'}, {L'Ð', L'ð'}, {L'Ñ', L'ñ'},
    {L'Ò', L'ò'}, {L'Ó', L'ó'}, {L'Ô', L'ô'}, {L'Õ', L'õ'}, {L'Ö', L'ö'}, {L'Ø', L'ø'},
    {L'Ù', L'ù'}, {L'Ú', L'ú'}, {L'Û', L'û'}, {L'Ü', L'ü'}, {L'Ý', L'ý'}, {L'Þ', L'þ'},
    {L'Ÿ', L'ÿ'},

    // Cyrillic
    {L'А', L'а'}, {L'Б', L'б'}, {L'В', L'в'}, {L'Г', L'г'}, {L'Д', L'д'}, {L'Е', L'е'},
    {L'Ё', L'ё'}, {L'Ж', L'ж'}, {L'З', L'з'}, {L'И', L'и'}, {L'Й', L'й'}, {L'К', L'к'},
    {L'Л', L'л'}, {L'М', L'м'}, {L'Н', L'н'}, {L'О', L'о'}, {L'П', L'п'}, {L'Р', L'р'},
    {L'С', L'с'}, {L'Т', L'т'}, {L'У', L'у'}, {L'Ф', L'ф'}, {L'Х', L'х'}, {L'Ц', L'ц'},
    {L'Ч', L'ч'}, {L'Ш', L'ш'}, {L'Щ', L'щ'}, {L'Ъ', L'ъ'}, {L'Ы', L'ы'}, {L'Ь', L'ь'},
    {L'Э', L'э'}, {L'Ю', L'ю'}, {L'Я', L'я'},

    // Greek
    {L'Α', L'α'}, {L'Β', L'β'}, {L'Γ', L'γ'}, {L'Δ', L'δ'}, {L'Ε', L'ε'}, {L'Ζ', L'ζ'},
    {L'Η', L'η'}, {L'Θ', L'θ'}, {L'Ι', L'ι'}, {L'Κ', L'κ'}, {L'Λ', L'λ'}, {L'Μ', L'μ'},
    {L'Ν', L'ν'}, {L'Ξ', L'ξ'}, {L'Ο', L'ο'}, {L'Π', L'π'}, {L'Ρ', L'ρ'}, {L'Σ', L'σ'},
    {L'Τ', L'τ'}, {L'Υ', L'υ'}, {L'Φ', L'φ'}, {L'Χ', L'χ'}, {L'Ψ', L'ψ'}, {L'Ω', L'ω'},
    {L'Ά', L'ά'}, {L'Έ', L'έ'}, {L'Ή', L'ή'}, {L'Ϊ', L'ϊ'}, {L'Ί', L'ί'}, 
    {L'Ό', L'ό'}, {L'Ύ', L'ύ'}, {L'Ϋ', L'ϋ'}, {L'Ώ', L'ω'},
};

